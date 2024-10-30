package senser;

import jsonstream.*;
import java.util.List;

import org.json.JSONArray;

import java.util.List;
import jsonstream.PlaneDataServer;
import observer.SimpleObservable;

public class Senser implements Runnable {
public class Senser extends SimpleObservable<AircraftSentence>
		implements Runnable {
    PlaneDataServer server;

    public Senser(PlaneDataServer server) {
            
            List<AircraftSentence> sentences = AircraftSentenceFactory.fromAircraftJson(planeArray.toString());
            
            AircraftDisplay.displayAircraftSentences(sentences);
			// AircraftDisplay.displayAircraftSentences(sentences);

			for (AircraftSentence sentence : sentences) { // aus lab 2
				setChanged();
				notifyObservers(sentence);
			}
        
        }
    }
}
