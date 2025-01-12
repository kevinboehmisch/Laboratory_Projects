import axios from "axios";
import { API_BASE_URL } from "../config/apiConfig";

const WorkoutService = {
    async saveWorkout(workout) {
        const response = await axios.post(`${API_BASE_URL}/workouts`, workout);
        return response.data; // Rückgabe des gespeicherten Workouts
    },
    async saveWorkoutDetails(details) {
        const response = await axios.post(`${API_BASE_URL}/workoutDetails/batch`, details);
        return response.data; // Rückgabe der gespeicherten Details
    },
    async getAllWorkoutsWithDetails() {
      try {
        const response = await axios.get(`${API_BASE_URL}/workouts/details`);
        const flatWorkouts = response.data; // Daten aus der API-Antwort
    
        // Gruppiere die Workouts nach WorkoutID
        const groupedWorkouts = flatWorkouts.reduce((acc, detail) => {
          const workoutID = detail.WorkoutID;
    
          if (!acc[workoutID]) {
            acc[workoutID] = {
              WorkoutID: detail.WorkoutID,
              Name: detail.WorkoutName,
              Details: [], // Initialisiere leeres Array für Details
            };
          }
    
          acc[workoutID].Details.push({
            UebungName: detail.UebungName,
            SatzNummer: detail.SatzNummer,
            Gewicht: detail.Gewicht,
            Wiederholungen: detail.Wiederholungen,
            Completed: detail.Completed,
          });
    
          return acc;
        }, {});
    
        // Konvertiere das Objekt zurück in ein Array
        return Object.values(groupedWorkouts); // Gruppierte Workouts
      } catch (error) {
        console.error("Fehler beim Abrufen der Workouts mit Details:", error);
        throw error;
      }
    }
    
};

export default WorkoutService;
const flatWorkouts = await WorkoutService.getAllWorkoutsWithDetails(); // Flache Struktur laden
console.log("Flache Workouts-Daten:", flatWorkouts);

// Gruppiere die Daten nach WorkoutID

