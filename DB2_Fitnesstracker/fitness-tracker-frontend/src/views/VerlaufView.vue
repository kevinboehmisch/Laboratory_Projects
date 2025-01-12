<template>
    <div class="verlauf-view">
      <h1>Trainingseinheiten Verlauf</h1>
      <Verlauf
        :trainingseinheiten="trainingseinheiten"
        @open-modal="openModal"
      />
      <!-- Modal wird angezeigt, wenn eine Einheit ausgewählt ist -->
      <VerlaufDetailModal
        v-if="selectedEinheit"
        :einheit="selectedEinheit"
        @close="closeModal"
      />
    </div>
  </template>
  
  <script>
  import Verlauf from "../components/Verlauf.vue";
  import VerlaufDetailModal from "../components/VerlaufDetailModal.vue";
  import { trainingseinheiten } from "../data/verlauf";
  
  export default {
    name: "VerlaufView",
    components: {
      Verlauf,
      VerlaufDetailModal,
    },
    data() {
      return {
        trainingseinheiten, // Importierte Mockdaten
        selectedEinheit: null, // Zum Öffnen des Modals
      };
    },
    methods: {
 
    },
  };
  </script>
  
  <style scoped>
  .verlauf-view {
    padding: 2rem;
  }
  
  h1 {
    margin-bottom: var(--margin-bottom-header);
  }
  </style>
  