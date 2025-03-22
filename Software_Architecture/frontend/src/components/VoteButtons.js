import React, { useState, useEffect } from "react";
import axios from "axios";
import { initializeKeycloak } from "../Keycloak";

const apiURL = process.env.API_URL || "http://localhost:8080";

const VoteButtons = ({ postId }) => {
  const [voteCount, setVoteCount] = useState(0);
  const [userId, setUserId] = useState(null);

  useEffect(() => {
    initializeKeycloak()
      .then((keycloak) => {
        const username = keycloak.tokenParsed?.preferred_username || "unknown-user";
        setUserId(username);
      })
      .catch((err) => console.error("Keycloak-Fehler:", err));
  }, []);

  useEffect(() => {
    axios
      .get(`${apiURL}/votes/${postId}/count`)
      .then((response) => setVoteCount(response.data))
      .catch((error) => console.error("Fehler beim Abrufen des Vote-Counts:", error));
  }, [postId]);

  const handleVote = (direction) => {
    if (!userId) return;

    axios
      .post(`${apiURL}/votes/${postId}/${direction}`, null, {
        params: { userId: userId },
      })
      .then(() => axios.get(`${apiURL}/votes/${postId}/count`))
      .then((response) => setVoteCount(response.data))
      .catch((error) => console.error("Fehler beim Voting:", error));
  };

  return (
    <div className="vote-buttons">
      <p className="vote-count">Votes: {voteCount}</p>
      <button className="vote-button" onClick={() => handleVote("up")}>
        😊
      </button>
      <button className="vote-button" onClick={() => handleVote("down")}>
        😠
      </button>
    </div>
  );
};

export default VoteButtons;