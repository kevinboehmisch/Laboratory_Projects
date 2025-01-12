<template>
    <div class="modal-overlay" @click.self="closeModal">
      <div class="modal">
        <div class="header">
          <button class="modal-button" @click="closeModal">x</button>
          <h2>Workout erstellen</h2>
        </div>
        <div class="modal-content">
          <!-- Workout-Name -->
          <div class="form-group">
            <h3 for="workout-name">Workout-Name</h3>
            <input
              id="workout-name"
              v-model="newWorkout.name"
              type="text"
              placeholder="Workout Name"
            />
          </div>
  
          <!-- Übungen-Auswahl -->
          <div class="uebung-list">
            <h3>Übungen auswählen:</h3>
            <div
              v-for="uebung in uebungen"
              :key="uebung.uebungID"
              class="uebung-card"
              @click="toggleSelection(uebung)"
              :class="{ selected: newWorkout.exercises.includes(uebung) }"
            >
              <h4 class="uebungen-beschreibung-header">{{ uebung.name }}</h4>
              <p class="uebungen-beschreibung-text">{{ uebung.muskelgruppe }}</p>
            </div>
          </div>
  
          <!-- Weiter-Button -->
          <button class="save-button" @click="nextStep">Weiter</button>
        </div>
      </div>
    </div>
  </template>
  
  <script>
  import UebungService from "../services/UebungService";
  
  export default {
    name: "AddWorkoutModal",
    data() {
      return {
        newWorkout: {
          name: "",
          exercises: [],
        },
        uebungen: [], // Hier werden die Übungen aus dem Backend gespeichert
      };
    },
    async mounted() {
      try {
        const uebungen = await UebungService.getAllUebungen(); // Übungen vom Backend laden
        this.uebungen = uebungen;
        console.log("Geladene Übungen:", this.uebungen); // Debugging-Ausgabe
      } catch (error) {
        console.error("Fehler beim Laden der Übungen:", error);
      }
    },
    methods: {
      closeModal() {
        this.$emit("close");
      },
      toggleSelection(uebung) {
        const index = this.newWorkout.exercises.findIndex(
          (exercise) => exercise.uebungID === uebung.uebungID
        );
        if (index === -1) {
          this.newWorkout.exercises.push(uebung);
        } else {
          this.newWorkout.exercises.splice(index, 1);
        }
      },
      nextStep() {
  if (!this.newWorkout.name || this.newWorkout.exercises.length === 0) {
    alert("Bitte geben Sie einen Namen ein und wählen Sie Übungen aus.");
    return;
  }
  console.log("Daten, die an das nächste Modal übergeben werden:", this.newWorkout);
  this.$emit("next", this.newWorkout);
}

    },
  };
  </script>
  
  
  <style scoped>
  .modal-overlay {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background: rgba(0, 0, 0, 0.5);
    display: flex;
    justify-content: center;
    align-items: center;
    backdrop-filter: blur(8px);
    z-index: 1000;
  }
  
  .modal {
    background-color: var(--card-background-color);
    padding: var(--card-padding);
    margin: 20px;
    border-radius: var(--border-radius);
    max-width: 500px;
    width: 90%;
    max-height: 90vh; /* Begrenzte Höhe des Modals */
    display: flex;
    flex-direction: column;
  }
  
  .header {
    display: flex;
    align-items: center;
    justify-content: center;
    position: relative;
  }
  
  .header h2 {
    margin: 0 auto;
    text-align: center;
  }
  
  .modal-button {
    position: absolute;
    right: 0;
    top: 0;
    background: none;
    border: none;
    color: var(--text-primary-color);
    font-size: 18px;
    cursor: pointer;
  }
  
  .modal-content {
    flex: 1;
    overflow-y: auto; /* Ermöglicht vertikales Scrollen */
    padding: 1rem 0; /* Zusätzlicher Abstand innerhalb des Inhalts */
  }
  
  .form-group {
    margin-bottom: 1rem;
  }
  
  .form-group label {
    display: block;
    margin-bottom: 0.5rem;
    color: var(--text-primary-color);
  }
  
  .form-group input {
    width: 60%;
    padding: 0.5rem;
    border: 1px solid var(--text-secondary-color);
    border-radius: 10px;
    background-color: var(--background-color);
    color: var(--text-primary-color);
  }
  
  .uebung-list {
  display: flex;
  flex-direction: column;
  gap: 15px;
  max-height: 490px; /* Begrenzte maximale Höhe für die Liste */
  overflow-y: auto; /* Aktiviert Scrollen, falls der Inhalt die Höhe überschreitet */
  padding-right: 5px; /* Optional: etwas Platz für den Scrollbalken */
}

  
  .uebung-card {
    border-radius: var(--border-radius);
    background-color: var(--background-color);
    color: var(--text-primary-color);
    display: flex;
    flex-direction: column;
    text-align: center;
    cursor: pointer;
    transition: background-color 0.3s, color 0.3s;
  }
  
  .uebung-card.selected {
    background-color: var(--link-color);
    color: white;
  }
  
  .save-button {
    margin-top: 35px;
    padding: 0.5rem 1rem;
    background-color: var(--link-color);
    border: none;
    border-radius: var(--border-radius);
    color: white;
    cursor: pointer;
    transition: background-color 0.3s;
  }
  
  .save-button:hover {
    background-color: var(--link-hover-color);
  }

  .uebungen-beschreibung-header{
    padding-top: 10px;
    margin: 0px;

  }
  .uebungen-beschreibung-text{
    padding-bottom: 10px;
    margin: 0px;
    color: var(--text-secondary-color);
  }
  </style>
  