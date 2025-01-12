<template>
  <div class="uebungen">
    <div v-for="uebung in uebungen" :key="uebung.id" class="uebung-card" @click="openModal(uebung)">
      <h3>{{ uebung.name }}</h3>
      <p>{{ uebung.muskelgruppe }}</p>
    </div>

    <!-- Modal für Übungsdetails -->
    <UebungenDetailModal v-if="selectedUebung" :uebung="selectedUebung" @save="handlesave" @close="closeModal" />
  </div>
</template>

<script>
import UebungenDetailModal from './UebungenDetailModal.vue';
import UebungService from "../services/UebungService"; // Pfad anpassen, falls erforderlich
import { EventBus } from "../plugins/eventBus";


export default {
  name: "Uebungen",
  components: {
    UebungenDetailModal,
  },
  data() {
    return {
      uebungen: [], // Übungen aus dem Backend
      selectedUebung: null, // Aktuell ausgewählte Übung
    };
  },
  mounted() {

    // EventBus abonnieren
    this.$watch(
      () => EventBus.newUebung,
      (newUebung) => {
        if (newUebung) {
          this.uebungen.push(newUebung); // Neue Übung hinzufügen
          fetchUebungen();
          EventBus.newUebung = null; // Event zurücksetzen
        }
      }
    );
  },
  methods: {
    async fetchUebungen() {
      try {
        this.uebungen = await UebungService.getAllUebungen();
      } catch (error) {
        console.error("Fehler beim Abrufen der Übungen:", error);
      }
    },
    openModal(uebung) {
      this.selectedUebung = uebung;
    },
    closeModal() {
      this.selectedUebung = null;
    },

    async handleSave(newUebung) {
      try {
        const createdUebung = await UebungService.createUebung(newUebung);
        this.uebungen.push(createdUebung);
        fetchUebungen();
        this.closeModal();
      } catch (error) {
        console.error("Fehler beim Speichern:", error);
      }
    },
  },
  created() {
    this.fetchUebungen(); // Daten abrufen, wenn die Komponente erstellt wird
  },
};

</script>

<style scoped>
.uebungen {
  display: flex;
  /* Flexbox verwenden */
  flex-direction: column;
  /* Vertikale Anordnung */
  gap: 20px;
  /* Abstand zwischen den Karten */
  width: 600px;
}

.uebung-card {
  padding: 15px;
  border-radius: var(--border-radius);
  background-color: var(--card-background-color);
  text-align: center;
  cursor: pointer;
  /* Zeigt an, dass das Element klickbar ist */
  transition: transform 0.2s ease;
}

.uebung-card h3 {
  margin: 0;
  font-size: 1.2rem;
}

.uebung-card p {
  margin: 0;
  color: var(--text-secondary-color);
  font-size: 0.9rem;
}
</style>
