package acamo;

import de.saring.leafletmap.*;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.concurrent.Worker;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import messer.BasicAircraft;
import messer.Messer;
import observer.Observable;
import observer.Observer;
import senser.Senser;
import jsonstream.PlaneDataServer;

import java.util.*;
import java.util.concurrent.CompletableFuture;

public class Acamo extends Application implements Observer<BasicAircraft> {

    private TableView<BasicAircraft> tableView;
    private ObservableList<BasicAircraft> aircraftList = FXCollections.observableArrayList();
    private ActiveAircrafts activeAircrafts;
    private GridPane selectedAircraftPane;

    private static double latitude = 48.7433425;
    private static double longitude = 9.3201122;
    private static boolean haveConnection = true;
    private boolean updatedMarker = false;

    private PlaneDataServer server;
    private String urlString = "https://opensky-network.org/api/states/all";

    private LeafletMapView map;
    private Marker baseStationMarker;
    private HashMap<String, Marker> planes = new HashMap<>();
    

    private TextField setLatitude;
    private TextField setLongitude;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        // Initialize PlaneDataServer based on connection
        if (haveConnection) {
            server = new PlaneDataServer(urlString, latitude, longitude, 100);
        } else {
            server = new PlaneDataServer(latitude, longitude, 100);
        }

        Senser senser = new Senser(server);
        Messer messer = new Messer();
        senser.addObserver(messer);
        new Thread(messer).start();

        activeAircrafts = new ActiveAircrafts();
        messer.addObserver(activeAircrafts);
        messer.addObserver(this);

        new Thread(server).start();
        new Thread(senser).start();
        new Thread(messer).start();

        // Create and configure the table
        tableView = new TableView<>();
        tableView.setPrefSize(500, 400);

        ArrayList<String> attributes = BasicAircraft.getAttributesNames();
        for (String attribute : attributes) {
            TableColumn<BasicAircraft, Object> column = new TableColumn<>(attribute);
            column.setCellValueFactory(new PropertyValueFactory<>(attribute));
            tableView.getColumns().add(column);
        }

        tableView.setItems(aircraftList);

        // Pane to display selected aircraft details
        selectedAircraftPane = new GridPane();
        selectedAircraftPane.setPadding(new Insets(10));
        selectedAircraftPane.setHgap(10);
        selectedAircraftPane.setVgap(10);

        Label placeholderLabel = new Label("Select an aircraft to view details");
        GridPane.setColumnSpan(placeholderLabel, 2);
        selectedAircraftPane.add(placeholderLabel, 0, 0);

        // Event handler for table row selection
        tableView.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<BasicAircraft>() {
            @Override
            public void changed(ObservableValue<? extends BasicAircraft> observable, BasicAircraft oldValue, BasicAircraft newValue) {
                if (newValue != null) {
                    displaySelectedAircraft(newValue);
                }
            }
        });

        VBox rightSection = new VBox(20); // VBox to hold the map and input section
        rightSection.setPadding(new Insets(10));

        // Call initializeMap and setBaseStation
        initializeMap(rightSection);
        setBaseStation(rightSection);

        HBox mainLayout = new HBox(20, tableView, rightSection); // Spacing of 20 between table and right section
        HBox.setHgrow(tableView, Priority.ALWAYS);
        HBox.setHgrow(rightSection, Priority.ALWAYS);

        Scene scene = new Scene(mainLayout);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Active Aircrafts");
        primaryStage.sizeToScene();
        primaryStage.setOnCloseRequest(e -> System.exit(0));
        primaryStage.show();
    }

    private void initializeMap(VBox rightSection) {
        map = new LeafletMapView();
        LatLong pos = new LatLong(latitude, longitude);
        baseStationMarker = new Marker(pos, "Base Station", "basestation", 1);

        List<MapLayer> config = Collections.singletonList(MapLayer.OPENSTREETMAP);
        CompletableFuture<Worker.State> loadState = map.displayMap(
                new MapConfig(config, new ZoomControlConfig(), new ScaleControlConfig(), pos));

        loadState.whenComplete((state, throwable) -> {
            if (state == Worker.State.SUCCEEDED) {
                updatedMarker = true;
                for (int i = 0; i <= 24; i++) {
                    map.addCustomMarker(String.format("plane%02d", i), String.format("icons/plane%02d.png", i));
                }
                map.addCustomMarker("basestation", "icons/basestationlarge.png");
            
                map.setView(pos, 7);
                map.addMarker(baseStationMarker);
                map.onMapClick(newpos -> updateBaseStationCoordinates(newpos.getLatitude(), newpos.getLongitude()));
                updateAllAircraftMarkers();
            }
        });

        rightSection.getChildren().add(map);
    }

    private void setBaseStation(VBox rightSection) {
        Label latitudeLabel = new Label("Latitude:");
        setLatitude = new TextField(String.valueOf(latitude));

        Label longitudeLabel = new Label("Longitude:");
        setLongitude = new TextField(String.valueOf(longitude));

        Button submitButton = new Button("Update Base Station");

        submitButton.setOnAction(event -> {
            updateBaseStationCoordinates(
                Double.parseDouble(setLatitude.getText()),
                Double.parseDouble(setLongitude.getText()));
        });


        VBox inputSection = new VBox(10, latitudeLabel, setLatitude, longitudeLabel, setLongitude, submitButton);
        rightSection.getChildren().add(inputSection);
    }

    private void updateBaseStationCoordinates(double newLatitude, double newLongitude) {
        latitude = newLatitude;
        longitude = newLongitude;
        setLatitude.setText(String.valueOf(latitude));
        setLongitude.setText(String.valueOf(longitude));
        resetBaseStation();
    }

    @Override
    public void update(Observable<BasicAircraft> observable, BasicAircraft newBasicAircraftValue) {
        Platform.runLater(() -> {
            if (activeAircrafts != null) {
                activeAircrafts.update(observable, newBasicAircraftValue);
                aircraftList.setAll(activeAircrafts.values());
                if (updatedMarker) {
                    updateAllAircraftMarkers();
                }
            }
        });
    }

    private void displaySelectedAircraft(BasicAircraft aircraft) {
        selectedAircraftPane.getChildren().clear();

        int row = 0;

        addAircraftDetail(row++, "Selected Aircraft Details", "");
        addAircraftDetail(row++, "ICAO", aircraft.getIcao());
        addAircraftDetail(row++, "Operator", aircraft.getOperator());
        addAircraftDetail(row++, "Position Time", aircraft.getPosTime().toString());
        addAircraftDetail(row++, "Coordinate", aircraft.getCoordinate().toString());
        addAircraftDetail(row++, "Speed", String.valueOf(aircraft.getSpeed()));
        addAircraftDetail(row++, "Track", String.valueOf(aircraft.getTrak()));
    }

    private void addAircraftDetail(int row, String attributeName, String attributeValue) {
        Label nameLabel = new Label(attributeName + ": ");
        Label valueLabel = new Label(attributeValue);

        selectedAircraftPane.add(nameLabel, 0, row);
        selectedAircraftPane.add(valueLabel, 1, row);
    }

  

    private void resetBaseStation() {
        LatLong pos = new LatLong(latitude, longitude);
        baseStationMarker.move(pos);
        map.panTo(pos);
        emptyAircraftList();
        removeMarkers();
        server.resetLocation(latitude, longitude, 100);
    }

    private void updateAircraftMarkers(BasicAircraft basicAircraft) {
        LatLong pos = new LatLong(basicAircraft.getCoordinate().getLongitude(), basicAircraft.getCoordinate().getLatitude());
        String png = String.format("plane%02d", Math.round(basicAircraft.getTrak() / 15));

        planes.compute(basicAircraft.getIcao(), (icao, marker) -> {
            if (marker == null) {
                marker = new Marker(pos, icao, png, 1);
                map.addMarker(marker);
            } else {
                marker.move(pos);
                marker.changeIcon(png);
            }
            return marker;
        });
    }

    private void updateAllAircraftMarkers() {
        planes.keySet().removeIf(icao -> {
            if (aircraftList.stream().noneMatch(aircraft -> Objects.equals(aircraft.getIcao(), icao))) {
            	Marker marker = planes.remove(icao);
                if (marker != null) {
                    map.removeMarker(marker);
                }
                return true;
            }
            return false;
        });

        aircraftList.forEach(this::updateAircraftMarkers);
    }

    private void removeMarkers() {
        planes.values().forEach(map::removeMarker);
        planes.clear();
    }
    
    private void emptyAircraftList() {
        Platform.runLater(() -> {
            aircraftList.clear();
            activeAircrafts.clear();
        });
    }
}
