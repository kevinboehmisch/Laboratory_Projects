import React, { useEffect, useState } from "react";
import axios from "axios";
import CommentList from "./CommentList";
import VoteButtons from "./VoteButtons";

const apiURL = process.env.API_URL || "http://localhost:8080";

const PostList = () => {
  const [posts, setPosts] = useState([]);
  const [error, setError] = useState(null);
  const [latitude, setLatitude] = useState(null);
  const [longitude, setLongitude] = useState(null);
  const [locationError, setLocationError] = useState(null);

  // Geolocation automatisch abrufen
  useEffect(() => {
    if (navigator.geolocation) {
      navigator.geolocation.getCurrentPosition(
        (position) => {
          setLatitude(position.coords.latitude);
          setLongitude(position.coords.longitude);
        },
        (error) => {
          console.error("Fehler beim Abrufen der Position:", error);
          setLocationError("Konnte Position nicht ermitteln.");
        }
      );
    } else {
      setLocationError("Geolocation wird von deinem Browser nicht unterstützt.");
    }
  }, []);

  // Posts abrufen, wenn Geolocation bereit ist
  useEffect(() => {
    if (latitude !== null && longitude !== null) {
      axios
        .get(`${apiURL}/posts`, {
        //.get(`${apiUrl}/post`, {
          params: {
            latitude: latitude,
            longitude: longitude,
            radius: 10000, // Radius in Metern
          },
        })
        .then((response) => {
          setPosts(response.data);
        })
        .catch((err) => {
          console.error("Error fetching posts:", err);
          setError("Failed to load posts.");
        });
    }
  }, [latitude, longitude]); // Läuft, wenn die Position sich ändert


  return (
    <>
      <div className="container">
        <h1>Nearby Posts</h1>
        {locationError && <p style={{ color: "red" }}>{locationError}</p>}
        {error && <p style={{ color: "red" }}>{error}</p>}
        {!latitude || !longitude ? (
          <p>Position wird ermittelt...</p>
        ) : (
          <div>
            {posts.map((post) => (
              <div key={post.id} className="post">
                <div className="post-header">
                  
                  <img className="avatar" src="https://abs.twimg.com/sticky/default_profile_images/default_profile_normal.png" alt="User Avatar" />
                  <span className="username">{post.userId}</span>
                </div>
                <div className="post-content">{post.content}</div>
                <div className="post-meta">
                  <span className="location-info">
                    {post.latitude}, {post.longitude}
                  </span>
                </div>
                <div className="vote-buttons">
                  <VoteButtons postId={post.id} />
                </div>
                <div className="comment-list">
                  <CommentList postId={post.id} />
                </div>
              </div>
            ))}
          </div>
        )}
      </div>
    </>
  );
};

export default PostList;