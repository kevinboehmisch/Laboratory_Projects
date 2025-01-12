<template>
    <nav class="navbar">
      <div class="container">
        <span class="brand">Fitness Tracker</span>
        <ul class="nav-links">
          <li><router-link to="/verlauf">Verlauf</router-link></li>
          <li><router-link to="/">Home</router-link></li>
          <li><router-link to="/uebungen">Übungen</router-link></li>
        </ul>
      </div>
    </nav>
  </template>
  
  <style scoped>
  .navbar {
    background-color: var(--background-color); /* Nutzt die globale Hintergrundfarbe */
    color: var(--text-primary-color); /* Nutzt die globale Primär-Textfarbe */
    padding: 1rem;
    border-bottom: 1px solid rgba(255, 255, 255, 0.1); /* Dezente Abgrenzung */
  }
  
  .container {
    display: flex;
    justify-content: space-between;
    align-items: center;
    max-width: 1280px;
    margin: 0 auto;
    padding: 0 1rem; /* Seitliche Polsterung */
  }
  
  .nav-links {
    list-style: none;
    display: flex;
    gap: 1.5rem; /* Mehr Platz zwischen den Links */
  }
  
  .nav-links a {
    color: var(--text-primary-color); /* Globale Textfarbe */
    text-decoration: none;
    font-weight: 500;
  }
  
  .nav-links a:hover {
    color: var(--link-hover-color); /* Globale Hover-Farbe */
  }
  
  .brand {
    font-weight: bold;
    font-size: 1.5rem; /* Etwas größere Schrift für die Marke */
    color: var(--text-primary-color); /* Globale Textfarbe */
  }
  </style>
  