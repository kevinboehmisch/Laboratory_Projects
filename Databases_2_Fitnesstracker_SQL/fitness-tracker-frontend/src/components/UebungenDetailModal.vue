<template>
    <div class="modal-overlay" @click.self="closeModal">
      <div class="modal">
        <div class="header">
          <button class="modal-button" @click="closeModal">x</button>
          <h2>{{ uebung.UebungName }}</h2>
        </div>
  
        <div class="info-row">
          <span>Muskelgruppe: {{ uebung.Muskelgruppe }}</span>
        </div>
  
        <div class="modal-content">
          <h3>Beschreibung</h3>
          <p class="description-text">
            {{ uebung.Beschreibung }}
          </p>
          <div class="durchschnittswerte">
            <p>Ø Gewicht: {{ (uebung.DurchschnittlichesGewicht || 0).toFixed(1) }} kg</p>
          <p>Ø Wiederholungen: {{ (uebung.DurchschnittlicheWiederholungen || 0).toFixed(1) }}</p>
        
          </div>
         </div>
      </div>
    </div>
  </template>
  
  <script>
  export default {
    name: "UebungenDetailModal",
    props: {
      uebung: {
        type: Object,
        required: true,
      },
    },
    methods: {
      closeModal() {
        this.$emit("close");
      },
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
    display: flex;
    flex-direction: column;
  }
  
  .header {
    display: flex;
    align-items: center;
    justify-content: center;
    position: relative;
    margin-bottom: var(--card-padding);
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
  
  .info-row {
    font-size: 1rem;
    color: var(--text-secondary-color);
    text-align: left;
    padding-left: 30px;
  }
  
  .modal-content {
    flex: 1;
    overflow-y: auto;
  }
  
  .modal-content h3 {
    margin-bottom: 1rem;
    text-align: left;
    padding-left: 30px;
  }
  
  .description-text {
    text-align: left;
    padding-left: 30px;
    padding-right: 30px;
    color: var(--text-primary-color);
    line-height: 1.5;
  }

  .durchschnittswerte {
  display: flex; /* Aktiviert Flexbox */
  align-items: center; /* Elemente vertikal zentrieren */
  margin: 0;
  padding-left: 30px;
  color: var(--text-secondary-color);
  font-size: 0.9rem;
  gap: 150px; /* Optional: Abstand zwischen den Elementen */
}

  </style>
  