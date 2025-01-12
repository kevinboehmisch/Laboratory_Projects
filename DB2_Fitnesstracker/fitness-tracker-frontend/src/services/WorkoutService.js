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
  async getAllWorkoutsWithDetailsAndExercises() {
    try {
      // Workouts und Details abrufen
      const workoutsResponse = await axios.get(`${API_BASE_URL}/workouts`);
      const workouts = workoutsResponse.data;

      // Übungen abrufen
      const uebungenResponse = await axios.get(`${API_BASE_URL}/uebungen`);
      const uebungen = uebungenResponse.data;

      // Workouts mit Details und Übungen verknüpfen
      const detailedWorkouts = await Promise.all(
        workouts.map(async (workout) => {
          const detailsResponse = await axios.get(
            `${API_BASE_URL}/workoutDetails/${workout.workoutID}`
          );
          const details = detailsResponse.data.map((detail) => ({
            ...detail,
            uebungName:
              uebungen.find((uebung) => uebung.uebungID === detail.uebungID)?.name || "Unbekannte Übung",
          }));

          return {
            ...workout,
            Details: details, // WorkoutDetails + Übungsnamen
          };
        })
      );

      return detailedWorkouts;
    } catch (error) {
      console.error("Fehler beim Laden der Workouts mit Details und Übungen:", error);
      throw error;
    }
  },
};

export default WorkoutService;
