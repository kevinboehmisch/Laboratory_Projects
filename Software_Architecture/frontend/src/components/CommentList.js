import React, { useState, useEffect } from "react";
import axios from "axios";

const apiURL = process.env.API_URL || "http://localhost:8080";

const CommentList = ({ postId }) => {
  const [comments, setComments] = useState([]);
  const [newComment, setNewComment] = useState("");

  useEffect(() => {
    axios
      .get(`${apiURL}/${postId}`)
      .then((response) => setComments(response.data))
      .catch((error) => console.error("Error fetching comments:", error));
  }, [postId]);

  const handleAddComment = () => {
    if (!newComment.trim()) return;

    axios
      .post(`${apiURL}/comments`, {
        text: newComment,
        post: { id: postId },
      })
      .then((response) => {
        setComments([...comments, response.data]);
        setNewComment("");
      })
      .catch((error) => console.error("Error adding comment:", error));
  };

  return (
    <div className="comment-list">
      <h3>Kommentare</h3>
      <div>
        {comments.map((comment) => (
          <div key={comment.id} className="comment">
            {comment.text}
          </div>
        ))}
      </div>
      <textarea
        className="comment-textarea"
        value={newComment}
        onChange={(e) => setNewComment(e.target.value)}
        placeholder="Schreibe einen Kommentar..."
      />
      <button className="comment-button" onClick={handleAddComment}>
        Kommentar hinzufügen
      </button>
    </div>
  );
};

export default CommentList;