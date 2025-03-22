import React from "react";
import { initializeKeycloak } from "../Keycloak";

const LogoutButton = () => {
  const handleLogout = () => {
    initializeKeycloak()
      .then((keycloak) => {
        keycloak.logout();
      })
      .catch((err) => {
        console.error("Fehler beim Abmelden:", err);
      });
  };

  return (
    <div className="logout-button-container">
      <button className="logout-button" onClick={handleLogout}>
        Abmelden
      </button>
    </div>
  );
};

export default LogoutButton;