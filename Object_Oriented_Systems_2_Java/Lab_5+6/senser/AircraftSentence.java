package senser;

import org.json.JSONArray;

public class AircraftSentence {
    private JSONArray aircraftData;

    public AircraftSentence(JSONArray aircraftData) {
        this.aircraftData = aircraftData;
    }
    /**
     * Diese Funktion gibt die Daten des Aircraftsentence als JSONArray zurück
     * @return JSONArray
     */
    public JSONArray getAircraftSentence() {
        return aircraftData;
    }
}
