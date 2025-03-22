import React, { useState, useEffect } from "react";
import PostList from "./components/PostList";
import PostForm from "./components/PostForm";
import LogoutButton from "./components/LogoutButton";

function App() {
  const [hasError, setHasError] = useState(false);
  const [darkMode, setDarkMode] = useState(false);

  // Beim Laden prüfen, ob Dark Mode gespeichert ist
  useEffect(() => {
    const savedMode = localStorage.getItem("darkMode");
    if (savedMode === "true") {
      setDarkMode(true);
      document.body.classList.add("dark-mode");
    }
  }, []);

  useEffect(() => {
    const handleError = (error) => {
      console.error("Globaler Fehler:", error);
      setHasError(true);
    };

    window.addEventListener("error", handleError);
    window.addEventListener("unhandledrejection", (e) =>
      handleError(e.reason || e)
    );

    return () => {
      window.removeEventListener("error", handleError);
      window.removeEventListener("unhandledrejection", handleError);
    };
  }, []);

  // Dark Mode umschalten und speichern
  const toggleDarkMode = () => {
    const newMode = !darkMode;
    setDarkMode(newMode);
    localStorage.setItem("darkMode", newMode); // Speichere den neuen Status
    document.body.classList.toggle("dark-mode", newMode);
  };

  if (hasError) {
    return (
      <div style={{ padding: "20px", textAlign: "center" }}>
        Ein Fehler ist aufgetreten. Prüfe die Konsole.
      </div>
    );
  }

  return (
    <>
      <header>
        <h1>Jodel App</h1>
        <button className="dark-mode-toggle" onClick={toggleDarkMode}>
          {darkMode ? "🌙" : "☀️"}
        </button>
        <div className="logout-button-container">
          <LogoutButton />
        </div>
      </header>
      <div className="container">
        <PostForm />
        <PostList />
      </div>
    </>
  );
}

export default App;