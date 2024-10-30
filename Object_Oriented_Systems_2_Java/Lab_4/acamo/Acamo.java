package acamo;

import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.stage.Stage;
import messer.BasicAircraft;
import messer.Messer;
import observer.Observable;
import observer.Observer;
import senser.Senser;
import jsonstream.PlaneDataServer;

import java.util.ArrayList;

public class Acamo extends Application implements Observer<BasicAircraft> {
    private TableView<BasicAircraft> tableView;
    private ObservableList<BasicAircraft> aircraftList;
    private ActiveAircrafts activeAircrafts;
    private GridPane selectedAircraftPane;
    
    private static double latitude = 48.7433425;
    private static double longitude = 9.3201122;
    private static boolean haveConnection = true;
    

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
    	
    	// Initialize and start the data source threads
    	String urlString = "https://opensky-network.org/api/states/all";
        PlaneDataServer server;

        // Initialisiere PlaneDataServer basierend auf der Verbindung
        if (haveConnection) {
            server = new PlaneDataServer(urlString, latitude, longitude, 100);
        } else {
            server = new PlaneDataServer(latitude, longitude, 100);
        }

        Senser senser = new Senser(server);
        new Thread(server).start();
        new Thread(senser).start();

        Messer messer = new Messer();
        senser.addObserver(messer);
        new Thread(messer).start();

        
        // Initialisiere ActiveAircrafts und füge Beobachter hinzu
        activeAircrafts = new ActiveAircrafts();
        messer.addObserver(activeAircrafts);
        messer.addObserver(this);
        
        activeAircrafts = new ActiveAircrafts();
        aircraftList = FXCollections.observableArrayList();

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

        HBox mainLayout = new HBox(20, tableView, selectedAircraftPane); // Spacing of 20 between table and details
        HBox.setHgrow(tableView, Priority.ALWAYS);
        HBox.setHgrow(selectedAircraftPane, Priority.ALWAYS);

        Scene scene = new Scene(mainLayout);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Active Aircrafts");
        primaryStage.sizeToScene();
        primaryStage.setOnCloseRequest(e->System.exit(0));
        primaryStage.show();
        

        
    }

    private void updateTable() {
        aircraftList.clear();
        aircraftList.addAll(activeAircrafts.values());
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

    @Override
    public void update(Observable<BasicAircraft> observable, BasicAircraft newValue) {
        if (newValue != null) {
            activeAircrafts.store(newValue.getIcao(), newValue);
            updateTable();
        }
    }
}
