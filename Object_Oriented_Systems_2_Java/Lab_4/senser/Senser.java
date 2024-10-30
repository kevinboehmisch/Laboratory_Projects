package senser;

import java.util.List;

import org.json.JSONArray;

import jsonstream.PlaneDataServer;
import observer.SimpleObservable;

public class Senser extends SimpleObservable<AircraftSentence>
		implements Runnable {
    PlaneDataServer server;

    public Senser(PlaneDataServer server) {
        this.server = server;
    }

    public void run() {
        while (true) {
            JSONArray planeArray = server.getPlaneArray();
            
            List<AircraftSentence> sentences = AircraftSentenceFactory.fromAircraftJson(planeArray.toString());
            
			// AircraftDisplay.displayAircraftSentences(sentences);

			for (AircraftSentence sentence : sentences) { // aus lab 2
				setChanged();
				notifyObservers(sentence);
			}
        
        }
    }
}
