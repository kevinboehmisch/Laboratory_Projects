<template>
  <div class="workouts-container">
    <h2 class="header">Deine Workouts</h2>
    <div class="workout-list">
      <div
        class="workout-card"
        v-for="workout in workouts"
        :key="workout.WorkoutID"
      >
        <h3 class="workout-name">{{ workout.Name }}</h3>
        <div class="uebungen-list">
          <div
            v-for="uebung in groupByUebung(workout.Details)"
            :key="uebung.UebungName"
            class="uebung-section"
          >
            <h4 class="uebung-name">{{ uebung.UebungName }}</h4>
            <ul class="satz-list">
  <li
    v-for="satz in uebung.Saetze"
    :key="satz.SatzNummer"
    class="satz-item"
  >
    <span class="satz-nummer">{{ satz.SatzNummer }}</span> 
    {{ satz.Gewicht }} kg x {{ satz.Wiederholungen }} 
  </li>
</ul>

          </div>
        </div>
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
  methods: {
    groupByUebung(details) {
  const grouped = new Map();

  details.forEach((detail) => {
    if (!grouped.has(detail.UebungName)) {
      grouped.set(detail.UebungName, {
        UebungName: detail.UebungName,
        Saetze: [],
      });
    }
    // Füge Satz hinzu
    const uebung = grouped.get(detail.UebungName);
    uebung.Saetze.push({
      Gewicht: detail.Gewicht,
      Wiederholungen: detail.Wiederholungen,
    });
  });

  // Satznummern nachträglich setzen
  return Array.from(grouped.values()).map((uebung) => {
    return {
      ...uebung,
      Saetze: uebung.Saetze.map((satz, index) => ({
        ...satz,
        SatzNummer: index + 1, // Satznummer beginnt bei 1 und zählt hoch
      })),
    };
  });
}

  },
};
</script>

  
  <style scoped>
.workouts-container {
  max-width: 500px;
  margin: 0 auto;
  padding: 1rem;
}

.workout-list {
  display: flex;
  flex-direction: column;
  gap: 20px;
}

.workout-card {
  background-color: var(--card-background-color);
  border-radius: var(--border-radius);
  padding: 20px;
  display: flex;
  flex-direction: column;
  gap: 15px;
  transition: transform 0.2s ease;
}

.workout-card:hover {
  transform: scale(1.02);
}

.workout-name {
  font-size: 1.2rem;
  color: var(--text-primary-color);
  margin: 0;
  text-align: center; /* Zentriert die Hauptüberschrift */
}

.uebungen-list {
  display: flex;
  flex-direction: column;
  gap: 10px;
  padding-left: 40px;
}

.uebung-section {
  background-color: var(--background-light-color);
  padding: 0px;
  text-align: left; /* Links ausgerichtet */
}

.uebung-name {
  font-size: 1rem;
  font-weight: bold;
  margin-top: 0px;
  margin-bottom: 3px;
  text-align: left; /* Links ausgerichtet */
}

.satz-list {
  list-style: none;
  margin: 0;
  padding: 0;
  display: flex;
  flex-direction: column;
  gap: 5px;
  text-align: left; /* Links ausgerichtet */
}

.satz-nummer {
  padding-right: 10px;
  padding-left: 30px;
  color: var(--text-secondary-color); /* Setzt eine spezielle Farbe für die Satznummer */
  margin:0px;
}
.satz-item {
  font-size: 0.9rem; /* Schriftgröße der ganzen Satzzeile */
  padding: 0px;
  margin:0px;
}

</style>

  
  