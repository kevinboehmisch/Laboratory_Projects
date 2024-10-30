package messer;



import java.util.concurrent.ConcurrentLinkedQueue;


import observer.*;
import senser.AircraftSentence;

public class Messer extends SimpleObservable<BasicAircraft>
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
            try {
                AircraftSentence sentence = queue.poll();
                if (sentence != null) {
                    BasicAircraft basicaircraft = factory.createBasicAircraft(sentence);
                    if (basicaircraft != null) {
                        display.displayAircraft(basicaircraft);
                        setChanged();
                        notifyObservers(basicaircraft);
                    }
                } else {
                    Thread.sleep(100);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

	}

	@Override
	public void update(Observable<AircraftSentence> observable,
			AircraftSentence newValue) {
		queue.add(newValue);
	}
}
