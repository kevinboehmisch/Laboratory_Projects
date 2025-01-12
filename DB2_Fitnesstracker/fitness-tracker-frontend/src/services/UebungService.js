import axios from "axios";
import { API_BASE_URL } from "../config/apiConfig";

const UebungService = {
  // GET: Alle Übungen abrufen
  async getAllUebungen() {
    try {
      const response = await axios.get(`${API_BASE_URL}/uebungen`);
      return response.data; // Gibt die Liste der Übungen zurück
    } catch (error) {
      console.error("Fehler beim Abrufen der Übungen:", error);
      throw error;
    }
  },

  // POST: Neue Übung erstellen
  async createUebung(uebung) {
    try {
      const response = await axios.post(`${API_BASE_URL}/uebungen`, uebung);
      return response.data; // Gibt die erstellte Übung zurück
    } catch (error) {
      console.error("Fehler beim Erstellen einer Übung:", error);
      throw error;
    }
  },
  // Übungen und die dazugehörigen durchschnittswerte bekommen
  async getExercisesWithAverages() {
    try {
        const response = await axios.get(`${API_BASE_URL}/uebungen/averages`);
        return response.data;
    } catch (error) {
        console.error("Fehler beim Abrufen der Übungen mit Durchschnittswerten:", error);
        throw error;
    }
}

};

export default UebungService;
