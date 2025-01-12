export const workouts = [
    {
      PlanID: 1,
      Name: "Push Day",
      Dauer: 45,
      Erstellungsdatum: "2025-01-10T12:00:00Z",
      Aktualisierungsdatum: "2025-01-11T12:00:00Z",
      Uebungen: [
        {
          UebungID: 101,
          Name: "Bankdrücken",
          Saetze: [
            { SatzNummer: 1, Gewicht: 80, Wiederholungen: 10, Completed: false },
            { SatzNummer: 2, Gewicht: 80, Wiederholungen: 10, Completed: false },
          ],
        },
        {
          UebungID: 102,
          Name: "Schulterdrücken",
          Saetze: [
            { SatzNummer: 1, Gewicht: 50, Wiederholungen: 12, Completed: false },
            { SatzNummer: 2, Gewicht: 50, Wiederholungen: 10, Completed: false },
          ],
        },
      ],
    },
    {
      PlanID: 2,
      Name: "Pull Day",
      Dauer: null,
      Erstellungsdatum: "2025-01-09T10:30:00Z",
      Aktualisierungsdatum: "2025-01-10T08:15:00Z",
      Uebungen: [
        {
          UebungID: 201,
          Name: "Klimmzüge",
          Saetze: [
            { SatzNummer: 1, Gewicht: 0, Wiederholungen: 8, Completed: false },
            { SatzNummer: 2, Gewicht: 0, Wiederholungen: 8, Completed: false },
          ],
        },
        {
          UebungID: 202,
          Name: "Rudern",
          Saetze: [
            { SatzNummer: 1, Gewicht: 60, Wiederholungen: 10, Completed: false },
            { SatzNummer: 2, Gewicht: 60, Wiederholungen: 10, Completed: false },
          ],
        },
      ],
    },
    {
      PlanID: 3,
      Name: "Leg Day",
      Dauer: 60,
      Erstellungsdatum: "2025-01-08T15:45:00Z",
      Aktualisierungsdatum: "2025-01-09T13:20:00Z",
      Uebungen: [
        {
          UebungID: 301,
          Name: "Kniebeugen",
          Saetze: [
            { SatzNummer: 1, Gewicht: 100, Wiederholungen: 8, Completed: true },
            { SatzNummer: 2, Gewicht: 100, Wiederholungen: 8, Completed: true },
          ],
        },
        {
          UebungID: 302,
          Name: "Beinpresse",
          Saetze: [
            { SatzNummer: 1, Gewicht: 120, Wiederholungen: 10, Completed: true },
            { SatzNummer: 2, Gewicht: 120, Wiederholungen: 10, Completed: true },
          ],
        },
      ],
    },
  ];
  