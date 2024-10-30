package messer;


import java.util.concurrent.ConcurrentLinkedQueue;

import observer.Observable;
import observer.Observer;
import observer.SimpleObservable;
import senser.AircraftSentence;

public class Messer extends SimpleObservable<AircraftSentence>
		implements Runnable, Observer<AircraftSentence> {

	private ConcurrentLinkedQueue<AircraftSentence> queue;

	public Messer() {
		this.queue = new ConcurrentLinkedQueue<AircraftSentence>();
	}


	public void run() {
		// notwendig, da in Java ein Objekt benötigt wird, ansonsten kann man
		// die Funktion der Klasse nicht aufrufen
		AircraftFactory factory = new AircraftFactory();
		AircraftDisplay display = new AircraftDisplay();

		while (true) {
			if (!queue.isEmpty()) {

				AircraftSentence sentence = queue.poll();
				BasicAircraft aircraft = factory.createBasicAircraft(sentence);
				setChanged();
				notifyObservers(sentence);
				display.displayAircraft(aircraft);
			}

		}
	}

	@Override
	public void update(Observable<AircraftSentence> observable,
			AircraftSentence newValue) {
		queue.add(newValue);
	}
}
