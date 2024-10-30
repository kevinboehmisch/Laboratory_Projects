package senser;

import jsonstream.*;
import org.json.JSONArray;

import jsonstream.*;
import java.util.List;

public class Senser implements Runnable
{
	PlaneDataServer server;
public class Senser implements Runnable {
    PlaneDataServer server;

	public Senser(PlaneDataServer server)
	{
		this.server = server;
	}
    public Senser(PlaneDataServer server) {
        this.server = server;
    }

	private String getSentence()
	{
		String list = server.getPlaneListAsString();
		return list;
	}
	
	public void run()
	{
		String aircraftList;
		JSONArray planeArray;
		
		while (true)
		{
			aircraftList = getSentence();
			System.out.println(aircraftList);
			
			planeArray = server.getPlaneArray();
			System.out.println(planeArray);
		}		
	}
}
    public void run() {
        while (true) {
            JSONArray planeArray = server.getPlaneArray();
            
            List<AircraftSentence> sentences = AircraftSentenceFactory.fromAircraftJson(planeArray.toString());
            
            AircraftDisplay.displayAircraftSentences(sentences);

// test
        
        }
    }
}
