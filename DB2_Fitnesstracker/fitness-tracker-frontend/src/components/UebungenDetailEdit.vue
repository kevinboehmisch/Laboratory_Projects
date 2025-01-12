<template>
    <div class="modal-overlay" @click.self="closeModal">
      <div class="modal">
        <div class="header">
          <button class="modal-button" @click="closeModal">x</button>
          <h2>Übung hinzufügen</h2>
        </div>
  
        <div class="modal-content">
          <!-- Formular für Name -->
          <div class="form-group">
            <label for="name">Übungsname</label>
            <input id="name" v-model="editData.name" type="text" placeholder="Neue Übung"  />
          </div>
  
          <!-- Formular für Muskelgruppe -->
          <div class="form-group">
            <label for="muskelgruppe">Muskelgruppe</label>
            <input id="muskelgruppe" v-model="editData.muskelgruppe" type="text" placeholder="Muskelgruppe" />
          </div>
  
          <!-- Formular für Beschreibung -->
          <div class="form-group">
            <label for="beschreibung">Beschreibung</label>
            <textarea
              id="beschreibung"
              v-model="editData.beschreibung"
              placeholder="Schritte hier eingeben..."
              rows="6"
            ></textarea>
          </div>
  
          <!-- Speichern-Button -->
          <button class="save-button" @click="saveChanges">Speichern</button>
        </div>
      </div>
    </div>
  </template>
  
  <script>
import UebungService from "../services/UebungService";
import { EventBus } from "../plugins/eventBus";

export default {
  name: "UebungenDetailEdit",
  props: {
    initialUebung: {
      type: Object,
      required: false, // Für neue oder bearbeitete Übungen
    },
  },
  data() {
    return {
      editData: {
        name: this.initialUebung?.name || "",
        muskelgruppe: this.initialUebung?.muskelgruppe || "",
        beschreibung: this.initialUebung?.beschreibung || "",
      },
    };
  },
  methods: {
    closeModal() {
      this.$emit("close");
    },
    async saveChanges() {
      try {
        const neueUebung = {
          name: this.editData.name,
          muskelgruppe: this.editData.muskelgruppe,
          beschreibung: this.editData.beschreibung,
        };
        const savedUebung = await UebungService.createUebung(neueUebung);
        EventBus.newUebung = savedUebung; // Event feuern
        this.$emit("save", neueUebung); // Emitiere die neu erstellte Übung

        this.closeModal();
      } catch (error) {
        console.error("Fehler beim Erstellen der Übung:", error);
      }
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
    max-width: 400px;
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
  
  .modal-content {
    flex: 1;
    overflow-y: auto;
    padding-top: 1rem;
  }
  
  .form-group {
    margin-bottom: 1rem;
  }
  
  .form-group label {
    display: block;
    margin-bottom: 0.5rem;
    color: var(--text-primary-color);
  }
  
  .form-group input,
  .form-group textarea {
    width: 80%;
    padding: 0.5rem;
    border: 1px solid var(--text-secondary-color);
    border-radius: 10px;
    background-color: var(--background-color);
    color: var(--text-primary-color);
  }
  
  textarea {
    resize: none; /* Kein manuelles Ändern der Größe */
  }
  
  .save-button {
    margin-top: 1rem;
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
  </style>
  