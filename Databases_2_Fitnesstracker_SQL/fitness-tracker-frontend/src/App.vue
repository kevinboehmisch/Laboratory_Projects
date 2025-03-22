<template>
  <div id="app">
    <div class="layout">
      <Navbar />
      <main class="main-content">
        <router-view />
      </main>
    </div>
  </div>
</template>

<script>
import Navbar from './components/Navbar.vue';

export default {
  components: {
    Navbar,
  },
};
</script>

<style>
/* Setze globale Stile */
body {
  margin: 0;
  font-family: Arial, sans-serif;
}

/* Container für das gesamte Layout */
.layout {
  display: flex;
  flex-direction: column;
  min-height: 100vh; /* Vollständige Fensterhöhe */
}

/* Navbar fixieren */
.navbar {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  z-index: 10; /* Überlappt den Inhalt */
}

/* Inhalt unter der Navbar */
.main-content {
  margin-top: 70px; /* Höhe der Navbar */
  padding: 20px; /* Innenabstand */
}
</style>
