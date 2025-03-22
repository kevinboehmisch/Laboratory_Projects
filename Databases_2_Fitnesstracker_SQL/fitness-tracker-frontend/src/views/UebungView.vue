<template>
    <div class="uebung-view">
      <h1 class="header">Übungen</h1>
      <AddButton @click="openAddModal">Übung hinzufügen</AddButton>
  
      <!-- Modal (Detail oder Bearbeiten/Hinzufügen) -->
      <UebungenDetailEdit
        v-if="selectedUebung !== null"
        :initialUebung="selectedUebung"
        @close="closeModal"

      />
  
      <div class="uebungen-container">
        <h2 class="header">Meine Übungen</h2>
        <Uebungen :uebungen="uebungen" @select="openDetailModal" />
      </div>
    </div>
  </template>
  
  <script>

  import Uebungen from "../components/Uebungen.vue";
  import AddButton from "../components/AddButton.vue";
  import UebungenDetailEdit from "../components/UebungenDetailEdit.vue";
  
  export default {
    name: "UebungView",
    components: {
      Uebungen,
      AddButton,
      UebungenDetailEdit,
    },
    data() {
      return {
        uebungen: [], // Wird dynamisch aus der API geladen
        selectedUebung: null, // Aktuell ausgewählte oder neue Übung
      };
    },

    methods: {
     
      openAddModal() {
        this.selectedUebung = {}; // Leere Übung für das Hinzufügen
      },
      openDetailModal(uebung) {
        this.selectedUebung = { ...uebung }; // Kopie der Übung für die Bearbeitung
      },
      closeModal() {
        this.selectedUebung = null;
      },
      
    },
  };
  </script>
  
  
  
  <style scoped>
  .header {
    margin-bottom: 25px;
  }
  
  .uebung-view {
    padding: 2rem;
    display: flex;
    flex-direction: column;
    gap: var(--margin-bottom-header);
    align-items: center;
  }
  
  .uebungen-container {
    margin-top: 15px;
  }
  </style>
  