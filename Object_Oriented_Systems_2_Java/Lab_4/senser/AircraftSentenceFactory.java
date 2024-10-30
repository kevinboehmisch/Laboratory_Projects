package senser;

import org.json.JSONArray;
import java.util.ArrayList;
import java.util.List;

public class AircraftSentenceFactory {

    public static List<AircraftSentence> fromAircraftJson(String jsonAircraftList) {
        List<AircraftSentence> sentences = new ArrayList<>();
        JSONArray jsonArray = new JSONArray(jsonAircraftList);

       
        for (int i = 0; i < jsonArray.length(); i++) {
            JSONArray aircraftData = jsonArray.getJSONArray(i);
            sentences.add(new AircraftSentence(aircraftData));
        }

        return sentences;
    }
}