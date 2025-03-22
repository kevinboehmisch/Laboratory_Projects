<template>
    <div class="modal-overlay" @click.self="closeModal">
        <div class="modal">
            <div class="header">
                
                <h2>{{ workout.Name }}</h2>
                <button class="modal-button" @click="closeModal">x</button>
            </div>

            <!-- Übungen und Sätze -->
            <div class="modal-content">
                <div v-for="uebung in workout.Uebungen" :key="uebung.uebungID" class="uebungen-section">
                    <h3 class="uebung-title">{{ uebung.name }}</h3>
                    <div class="saetze-header">
                        <span>Gewicht</span>
                        <span>Wiederholungen</span>
                    </div>
                    <div class="saetze-list">
                        <div v-for="(satz, index) in uebung.Saetze" :key="satz.SatzNummer" class="saetze-item">
                            <input
                                type="number"
                                v-model="satz.Gewicht"
                                placeholder="Gewicht"
                                class="saetze-input"
                            />
                            <input
                                type="number"
                                v-model="satz.Wiederholungen"
                                placeholder="Wdh."
                                class="saetze-input"
                            />
                            <button
                                class="completion-button"
                                :class="{ completed: satz.Completed }"
                                @click="toggleCompletion(uebung.uebungID, index)"
                            >
                                <span v-if="satz.Completed">+</span>
                                <span v-else>+</span>
                            </button>
                        </div>
                        <button class="add-saetze-button" @click="addSaetze(uebung.uebungID)">
                            Satz hinzufügen
                        </button>
                    </div>
                </div>
            </div>

            <button class="save-button" @click="saveWorkout">Speichern</button>
        </div>
    </div>
</template>

<script>

import WorkoutService from "../services/WorkoutService";

export default {
    name: "WorkoutDetailModal",
    props: {
        workout: {
            type: Object,
            required: true,
        },
    },
    methods: {
        closeModal() {
            this.$emit("close");
        },
        addSaetze(uebungId) {
            const uebung = this.workout.Uebungen.find((u) => u.uebungID === uebungId);
            if (uebung) {
                uebung.Saetze.push({
                    Gewicht: 0,
                    Wiederholungen: 0,
                    SatzNummer: uebung.Saetze.length + 1,
                });
            }
        },
        toggleCompletion(uebungId, index) {
            const uebung = this.workout.Uebungen.find((u) => u.uebungID === uebungId);
            if (uebung) {
                uebung.Saetze[index].Completed = !uebung.Saetze[index].Completed;
            }
        },
        async saveWorkout() {
    try {
        // Schritt 1: Workout speichern
        const savedWorkout = await WorkoutService.saveWorkout({
            name: this.workout.Name,
            gesamtdauer: this.workout.Gesamtdauer || null,
        });

        console.log("Gespeichertes Workout:", savedWorkout);

        // Schritt 2: Workout-Details speichern
        const detailsPayload = this.workout.Uebungen.flatMap((uebung) =>
            uebung.Saetze.map((satz) => ({
                workoutID: savedWorkout.workoutID,
                uebungID: uebung.uebungID,
                satzNummer: satz.SatzNummer,
                gewicht: satz.Gewicht,
                wiederholungen: satz.Wiederholungen,
                completed: satz.Completed || false,
            }))
        );

        await WorkoutService.saveWorkoutDetails(detailsPayload);
        console.log("Workout-Details gespeichert:", detailsPayload);

        // Modal schließen und Benutzer informieren
        alert("Workout erfolgreich gespeichert!");
        this.closeModal();
    } catch (error) {
        console.error("Fehler beim Speichern des Workouts oder der Details:", error);
        alert("Es gab ein Problem beim Speichern des Workouts.");
    }
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
    margin: 10px;
    border-radius: var(--border-radius);
    max-width: 400px; /* Schmaleres Modal */
    width: 100%;
    max-height: 70%;
    display: flex;
    flex-direction: column;
    align-items: center; /* Zentriert Inhalte horizontal */
    text-align: center; /* Zentriert Texte */
}

.header h2 {
    margin: 0 auto;
    text-align: center;
    overflow-x: hidden; 
}

.modal-button {
    position: absolute;
    top: 15%; /* Zentriert den Button vertikal innerhalb des Headers */
    transform: translateY(-50%); /* Korrigiert die Zentrierung */
    right: 460px; /* Abstand vom rechten Rand */
    background: none;
    border: none;
    color: var(--text-primary-color);
    font-size: 18px;
    cursor: pointer;
}

.modal-content {
    flex: 1;
    overflow-y: auto;
    display: flex;
    flex-direction: column;
    width: 80%;
    align-items: center; /* Zentriert Übungen */
    gap: 20px;
    overflow-x: hidden; 
}

.uebungen-section {
    margin-bottom: 1.5rem;
    width: 100%; /* Füllt den Container */
    display: flex;
    flex-direction: column;
    align-items: center; /* Zentriert Inhalte */
}

.saetze-header {
    display: flex;
    gap: 25px;
    width: 100%;
    margin-left: 110px;
    margin-bottom: 10px;
    text-align: center; /* Zentriert Überschriften */
}

.saetze-list {
    display: flex;
    flex-direction: column;
    gap: 10px;
    width: 100%;
}

.saetze-item {
    display: flex;
    align-items: center;
    gap: 10px;
    justify-content: center; /* Zentriert Sätze */
}

.saetze-input {
    width: 60px; /* Kleinere Eingabefelder */
    padding: 5px;
    border: 1px solid var(--text-secondary-color);
    border-radius: 6px; /* Abgerundete Ecken */
    background-color: black; /* Schwarzer Hintergrund */
    color: white; /* Weiße Schrift */
    text-align: center; /* Zentriert den Text in den Eingabefeldern */
}

.completion-button {
    background-color: #707070; /* Neutral grauer Button */
    border: none;
    border-radius: 6px; /* Abgerundete Ecken */
    padding: 4px 10px;
    cursor: pointer;
    color: rgb(255, 255, 255);
    transition: background-color 0.3s;
}

.completion-button.completed {
    background-color: var(--link-color); /* Farbe nach Statuswechsel */
    color: rgb(255, 255, 255);
    padding: 4px 10px;
    border: none;
}

.completion-button:hover {
    background-color: var(--link-hover-color);
    border: none;
}

.add-saetze-button {
    margin-top: 10px;
    margin-left: 85px;
    padding: 0.5rem 1rem;
    background-color: var(--link-color);
    border: none;
    border-radius: var(--border-radius);
    color: white;
    cursor: pointer;
    width: 150px;
    transition: background-color 0.3s;
}

.add-saetze-button:hover {
    background-color: var(--link-hover-color);
}

.save-button {
    margin-top: 1rem;
    padding: 0.5rem 1rem;
    background-color: var(--link-color);
    border: none;
    border-radius: var(--border-radius);
    color: white;
    cursor: pointer;
    width: 150px;
    transition: background-color 0.3s;
}

.save-button:hover {
    background-color: var(--link-hover-color);
}
</style>
