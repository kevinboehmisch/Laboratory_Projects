package senser;

import java.util.List;

public class AircraftDisplay {

    public static void displayAircraftSentences(List<AircraftSentence> aircraftSentences) {
      
        System.out.println("Current Aircrafts in range: " + aircraftSentences.size());
  
        for (AircraftSentence sentence : aircraftSentences) {
            System.out.println(sentence.getAircraftSentence().toString());
        }
    }
}
