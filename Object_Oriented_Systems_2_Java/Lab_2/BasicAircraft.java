package messer;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;


	private Double trak;

	
	public BasicAircraft (String icao, String operator, Date posTime, Coordinate coordinate, double speed, double trak) {
	public BasicAircraft(String icao, String operator, Date posTime, Coordinate coordinate, double speed, double trak) {
		this.icao = icao;
		this.operator = operator;
		this.posTime = posTime;
	{
		ArrayList<String> attributes = new ArrayList<String>();

		// TODO: return needed names
		attributes.addAll(Arrays.asList("icao", "operator", "posTime", "coordinate", "speed", "trak"));
		
		return attributes;
	}
	public static ArrayList<Object> getAttributesValues(BasicAircraft ac)
	{
		ArrayList<Object> attributes = new ArrayList<Object>();

		// TODO: return needed values
		
		attributes.addAll(Arrays.asList(ac.icao, ac.operator, ac.posTime, ac.coordinate, ac.speed, ac.trak));

		return attributes;
	}

	@Override
	public String toString() {
		return "BasicAircraft [icao=" + icao + ", operator=" + operator + ", posTime=" + posTime
				+ ", " + coordinate + coordinate + ", speed=" + speed + ", trak =" + trak + "]";
	}
}

