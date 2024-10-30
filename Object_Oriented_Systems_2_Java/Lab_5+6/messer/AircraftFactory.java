package messer;

import java.util.Date;

import org.json.JSONArray;

import senser.AircraftSentence;

public class AircraftFactory {

	public BasicAircraft createBasicAircraft(AircraftSentence sentence) {
		JSONArray sentenceArray = sentence.getAircraftSentence();
		BasicAircraft aircraft = new BasicAircraft(sentenceArray.getString(0),
				sentenceArray.getString(1),
				new Date(sentenceArray.getLong(3) * 1000),
				new Coordinate(sentenceArray.getDouble(5),
						sentenceArray.getDouble(6)),
				sentenceArray.getDouble(9), sentenceArray.getDouble(10));
		return aircraft;
	}
}
