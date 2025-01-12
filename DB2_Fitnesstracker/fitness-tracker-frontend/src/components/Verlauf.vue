<template>
    <div class="verlauf">
      <ul>
        <li v-for="einheit in trainingseinheiten" :key="einheit.id" class="training-item"  @click="handleClick(einheit)">
          <!-- Name des Plans -->
          <h3>{{ einheit.planName }}</h3>
  
          <!-- Datum und Dauer -->
          <div class="info-row">
            <span>{{ einheit.datum }}</span>
            <span class="duration">{{ einheit.dauer }}</span>
          </div>
  
          <!-- Sätze -->
          <div class="saetze">
            <div class="satz-header">
              <span class="uebung-header">Übungen</span>
              <span class="durchschnitt-header">Durchschnitt</span>
            </div>
            <div
              v-for="satz in einheit.saetze"
              :key="satz.uebung"
              class="satz-item"
            >
              <span class="uebung">{{ satz.anzahl }} x {{ satz.uebung }}</span>
              <span class="durchschnitt">
                {{ satz.durchschnittGewicht }} kg x {{ satz.durchschnittWiederholungen }}
              </span>
            </div>
          </div>
        </li>
      </ul>
    </div>
  </template>
  
  <script>
  export default {
    name: "Verlauf",
    props: {
      trainingseinheiten: {
        type: Array,
        required: true,
      },
    },
    methods: {
    handleClick(einheit) {
      this.$emit("open-modal", einheit);
    },
  },
  };
  </script>
  
  <style scoped>
  .verlauf {
    max-width: 500px;
    margin: 0 auto;
    padding: var(--padding);
  }
  
  ul {
    list-style: none;
    margin: 0; 
    padding: 0;
    display: flex;
    flex-direction: column;
    gap: var(--card-gap);
  }
  
  .training-item {
    background-color: var(--card-background-color);
    border-radius: var(--border-radius);
    display: flex;
    flex-direction: column;
    gap: 1rem;
    padding: var(--card-padding) 30px;
  }
  
  .training-item h3 {
    margin: 0;
    color: var(--text-primary-color);
  }
  
  /* Datum und Dauer in einer Zeile */
  .info-row {
    display: flex;
    justify-content: space-between;
    font-size: 0.9rem;
    color: var(--text-secondary-color);
  }
  
  /* Sätze-Auflistung */
  .saetze {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
  }
  
  /* Überschriften für Sätze */
  .satz-header {
    display: flex;
    justify-content: space-between;
    font-weight: bold;
    margin-bottom: 0.5rem;
  }
  
  .uebung-header {
    flex: 1;
    text-align: left;
  }
  
  .durchschnitt-header {
    flex: 1;
    text-align: right;
  }
  
  .satz-item {
    display: flex;
    justify-content: space-between;
    font-size: 0.95rem;
  }
  
  .uebung {
    flex: 1;
    text-align: left;
  }
  
  .durchschnitt {
    flex: 1;
    text-align: right;
    color: var(--text-secondary-color);
  }
  </style>
  