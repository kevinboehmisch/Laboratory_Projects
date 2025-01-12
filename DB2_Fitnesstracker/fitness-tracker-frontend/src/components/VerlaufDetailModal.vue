<template>
    <div class="modal-overlay" @click.self="closeModal">
        <div class="modal">

            <div class="header">
                <button class="modal-button" @click="closeModal">x</button>
                <h2>{{ einheit.planName }}</h2>

            </div>
            <div class="info-row">
                <span>{{ einheit.datum }}</span>
                <span class="duration">{{ einheit.dauer }}</span>
            </div>

            <div class="modal-content">
                <div v-for="satz in einheit.saetze" :key="satz.uebung" class="uebung">
                    <h3>{{ satz.uebung }}</h3>
                    <ul>
                        <li v-for="detail in satz.details" :key="detail.satzNummer" class="satz-item">
                            <span class="satz-index">{{ detail.satzNummer }}</span>
                            <span class="satz-details">
                                {{ detail.gewicht }}kg x {{ detail.wiederholungen }}
                            </span>
                        </li>
                    </ul>
                </div>
            </div>

        </div>
    </div>
</template>

<script>
export default {
    name: "VerlaufDetailModal",
    props: {
        einheit: {
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
    max-width: 600px;
    width: 450px;
    height: 600px;
    display: flex;
    flex-direction: column;
}



.info-row {
    display: flex;
    justify-content: space-between;
    font-size: 0.9rem;
    margin-bottom: 0px;
    color: var(--text-secondary-color);
    padding: 0 20px;
}

.modal-content {
    padding: 0px 0px 0px 50px;
    overflow-y: auto;
    flex: 1;

}

.uebung {
    margin-bottom: 1.5rem;
}

.uebung h3 {
    margin-bottom: 0.5rem;
    text-align: left;
}

.uebung ul {
    list-style: none;
    padding: 0;
    margin: 0;
}

.satz-item {
    display: grid;
    grid-template-columns: 30px 1fr;
    align-items: center;
    gap: 10px;
}

.satz-index {
    text-align: left;
    min-width: 30px;
    /* Einheitliche Breite für den Index */
    color: var(--text-secondary-color);
}

.satz-details {
    text-align: left;
    font-size: 15px;
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
    /* Mittig ausgerichtet */
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
</style>