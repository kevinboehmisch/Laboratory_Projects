<template>
  <div class="home-view">
    <h1 class="header">Workout beginnen</h1>
    <AddButton @click="openAddWorkoutModal">Workout hinzufügen</AddButton>

    <!-- Modal für neues Workout -->
    <AddWorkoutModal
      v-if="isModalOpen"
      :uebungen="uebungen"
      @close="closeModal"
      @next="openWorkoutDetailModal"
    />

    <!-- Modal für bestehendes oder neues Workout -->
    <WorkoutDetailModal
      v-if="selectedWorkout"
      :workout="selectedWorkout"
      @close="closeWorkoutModal"
      @save="saveWorkout"
    />

    <div class="workouts-container">
      <!-- Bestehende Workouts -->
      <Workouts :workouts="workouts" />
    </div>
  </div>
</template>

<script>
import WorkoutService from "../services/WorkoutService";
import Workouts from "../components/Workouts.vue";
import AddButton from "../components/AddButton.vue";
import AddWorkoutModal from "../components/AddWorkoutModal.vue";
import WorkoutDetailModal from "../components/WorkoutDetailModal.vue";

export default {
  name: "HomeView",
  components: {
    Workouts,
    AddButton,
    AddWorkoutModal,
    WorkoutDetailModal,
  },
  data() {
    return {
      workouts: [], // Workouts mit Details und Übungen
      uebungen: [], // Übungen
      isModalOpen: false, // Modal-Steuerung
      selectedWorkout: null, // Aktuell ausgewähltes Workout
    };
  },
  async mounted() {
    try {
      const detailedWorkouts = await WorkoutService.getAllWorkoutsWithDetailsAndExercises();
      this.workouts = detailedWorkouts; // Workouts im State speichern
      console.log("Geladene Workouts:", this.workouts); // Debugging
    } catch (error) {
      console.error("Fehler beim Laden der Workouts:", error);
    }
  },
  methods: {
  openAddWorkoutModal() {
    this.isModalOpen = true;
  },
  closeModal() {
    this.isModalOpen = false;
  },
  openWorkoutDetailModal(newWorkout) {
    this.isModalOpen = false;
    console.log("Neues Workout für Detailmodal:", newWorkout);
    this.selectedWorkout = {
      Name: newWorkout.name,
      Uebungen: newWorkout.exercises.map((uebung) => ({
        ...uebung,
        Saetze: [
          {
            Gewicht: 0,
            Wiederholungen: 0,
            SatzNummer: 1,
          },
        ],
      })),
    };
    console.log("Selected Workout:", this.selectedWorkout);
  },
  closeWorkoutModal() {
    this.selectedWorkout = null;
  },
},

};
</script>

<style scoped>
.header {
  margin-bottom: 25px;
}
.home-view {
  padding: 2rem;
  display: flex;
  flex-direction: column;
  gap: 1rem;
}
</style>
