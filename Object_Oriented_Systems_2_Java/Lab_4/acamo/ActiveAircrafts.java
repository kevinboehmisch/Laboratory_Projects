package acamo;

import java.util.ArrayList;
import java.util.HashMap;
import messer.BasicAircraft;
import observer.Observable;
import observer.Observer;

public class ActiveAircrafts implements ActiveAircraftsInterface, Observer<BasicAircraft> {
    private HashMap<String, BasicAircraft> activeAircrafts;

    public ActiveAircrafts() {
        this.activeAircrafts = new HashMap<>();
    }

    @Override
    public synchronized void store(String icao, BasicAircraft ac) {
        activeAircrafts.put(icao, ac);
    }

    @Override
    public synchronized void clear() {
        activeAircrafts.clear();
    }

    @Override
    public synchronized BasicAircraft retrieve(String icao) {
        return activeAircrafts.get(icao);
    }

    @Override
    public synchronized ArrayList<BasicAircraft> values() {
        return new ArrayList<>(activeAircrafts.values());
    }
    

    @Override
    public void update(Observable<BasicAircraft> observable, BasicAircraft newValue) {
        if (newValue != null) {
            store(newValue.getIcao(), newValue);
        }
    }
    
    public String toString() {
        return activeAircrafts.toString();
    }
    
    
}