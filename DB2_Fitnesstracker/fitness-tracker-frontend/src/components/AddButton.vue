<!-- src/components/AddButton.vue -->
<template>
    <button class="add-button" @click="handleClick">
      <slot>Hinzufügen</slot>
    </button>
  </template>
  
  <script>
  export default {
    name: "AddButton",
    props: {
      onClick: {
        type: Function,
        default: null, // Optional, falls keine Aktion benötigt wird
      },
    },
    methods: {
      handleClick() {
        if (this.onClick) {
          this.onClick();
        }
      },
    },
  };
  </script>
  
  <style scoped>
  .add-button {
    display: inline-flex;
    align-items: center;
    justify-content: center;
    width: 250px;
    padding: 20px;
    font-size: var(--heading-font-size);
    font-weight: bold;
    border-radius: var(--border-radius);
    background-color: var(--link-color);
    color: var(--text-primary-color);
    cursor: pointer;
    transition: background-color 0.3s ease, color 0.3s ease;
  }
  
  </style>
  