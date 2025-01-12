<template>
    <div class="workouts-container">
      <h2>Deine Workouts</h2>
      <div class="workout-list">
        <div
          class="workout-card"
          v-for="workout in workouts"
          :key="workout.workoutID"
        >
          <h3>{{ workout.name }}</h3>
          <ul>
            <li
              v-for="detail in workout.Details"
              :key="detail.workoutDetailID"
            >
              {{ detail.uebungName }}: {{ detail.gewicht }}kg x
              {{ detail.wiederholungen }} Wiederholungen
            </li>
          </ul>
        </div>
      </div>
    </div>
  </template>
  
  <script>
  export default {
    name: "Workouts",
    props: {
      workouts: {
        type: Array,
        required: true,
      },
    },
  };
  </script>
  
  <style scoped>
  .workouts-container {
    padding: 1rem;
  }
  .workout-list {
    display: flex;
    flex-direction: column;
    gap: 1rem;
  }
  .workout-card {
    padding: 1rem;
    border: 1px solid #ccc;
    border-radius: 8px;
  }
  </style>
  