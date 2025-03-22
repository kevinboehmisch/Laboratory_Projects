var localLogic = {
    playfield: [],
    moveCounter: 0,
    rows: 0,
    cols: 0,
    mines: 0,
    revealedCellsCount: 0,
    revealedCells: [],

    init: function(rows, cols, mines) {
        this.rows = rows;
        this.cols = cols;
        this.mines = mines;
        this.moveCounter = 0;
        this.revealedCellsCount = 0;
        this.playfield = [];
        this.revealedCells = [];

        for (let i = 0; i < rows; i++) {
            const row = [];
            for (let j = 0; j < cols; j++) {
                row.push(false); // false bedeutet keine Mine
            }
            this.playfield.push(row);
        }
        console.dir(this.playfield);
    },

    countMinesAround: function(x, y) {
        let count = 0;
        const directions = [
            [-1, -1], [-1, 0], [-1, 1],
            [0, -1], /*[0, 0],*/ [0, 1],
            [1, -1], [1, 0], [1, 1]
        ];

        for (let dir of directions) {
            const newX = x + dir[0];
            const newY = y + dir[1];

            if (newX >= 0 && newX < this.rows && newY >= 0 && newY < this.cols) {
                if (this.playfield[newX][newY]) {
                    count++;
                }
            }
        }

        return count;
    },

    updateRevealedCells: function(x, y) {
        const key = `${x},${y}`;
        if (!this.revealedCells.includes(key)) {
            this.revealedCells.push(key);
            this.revealedCellsCount++;
        }
    },

    getAllMines: function() {
        const mines = [];
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.cols; j++) {
                if (this.playfield[i][j]) {
                    mines.push([i, j]);
                }
            }
        }
        return mines;
    },

    revealEmptyCells: function(x, y) {
        const toDo = [[x, y]];
        const done = new Set();
        const emptyCells = [];

        while (toDo.length > 0) {
            const [curX, curY] = toDo.pop();
            const key = `${curX},${curY}`;

            if (!done.has(key)) {
                done.add(key);
                emptyCells.push([curX, curY]);
                this.updateRevealedCells(curX, curY);

                const directions = [
                    [-1, -1], [-1, 0], [-1, 1],
                    [0, -1], [0, 1],
                    [1, -1], [1, 0], [1, 1]
                ];

                for (let dir of directions) {
                    const newX = curX + dir[0];
                    const newY = curY + dir[1];

                    if (newX >= 0 && newX < this.rows && newY >= 0 && newY < this.cols &&
                        !done.has(`${newX},${newY}`) && !this.playfield[newX][newY]) {
                        if (this.countMinesAround(newX, newY) === 0) {
                            toDo.push([newX, newY]);
                        } else {
                            emptyCells.push([newX, newY]);
                            this.updateRevealedCells(newX, newY);
                        }
                    }
                }
            }
        }

        return emptyCells;
    },

    checkWin: function() {
        const totalCells = this.rows * this.cols;
        const nonMineCells = totalCells - this.mines;
        console.log(`Revealed cells count: ${this.revealedCellsCount}, Total non-mine cells: ${nonMineCells}`);
        return this.revealedCellsCount === nonMineCells;
    }
};

var remoteLogic = {
    baseURL: 'https://www2.hs-esslingen.de/~melcher/it/minesweeper/?',
    token: '',

    async init(userid, size, mines) {
        const response = await fetch(`${this.baseURL}request=init&userid=${userid}&size=${size}&mines=${mines}`);
        const data = await response.json();
        if (data.status === 'ok') {
            this.token = data.token;
            return data;
        } else {
            throw new Error(data.message);
        }
    },

    async sweep(x, y) {
        const response = await fetch(`${this.baseURL}request=sweep&token=${this.token}&x=${x}&y=${y}`);
        return response.json(); // Promise wird direkt zurückgegeben
    }
};

var minesweeper = {
    touchStartTime: null, // Variable zur Speicherung der Touch-Startzeit

    async init() {
        await this.generateBody();
    },

    async generateBody() {
        // Referenz auf den HTML-Body
        var body = document.body;

        // Neues Div-Element erstellen, das den gesamten Inhalt beinhaltet
        var contentDiv = document.createElement('div');
        contentDiv.classList.add('container');  // Verwendet die vorhandene CSS-Klasse

        // Header, Playfield, Button Bar und Footer generieren und anhängen
        contentDiv.appendChild(this.generateHeader());
        contentDiv.appendChild(this.generatePlayfield());
        contentDiv.appendChild(this.generateButtonBar());
        contentDiv.appendChild(this.generateFooter());

        // contentDiv an den Body anhängen
        body.appendChild(contentDiv);

        // Spielfeld für den Standardmodus generieren
        await this.newGame('small');
    },

    generateHeader() {
        // Header-Element erstellen
        const header = document.createElement('header');
        header.innerHTML = `
            <div class="title">
                <h1>Minesweeper</h1>
                <p>by Kevin Böhmisch</p>
            </div>
        `;
        return header;
    },

    generatePlayfield() {
        // Playfield-Element erstellen
        const playfield = document.createElement('div');
        playfield.id = 'playfield';
        return playfield;
    },

    generateButtonBar() {
        // Button Bar-Element erstellen
        const buttonBar = document.createElement('div');
        buttonBar.id = 'buttons';

        // Buttons generieren und anhängen
        buttonBar.appendChild(this.generateButton('small', 'small'));
        buttonBar.appendChild(this.generateButton('medium', 'medium'));
        buttonBar.appendChild(this.generateButton('large', 'large'));

        return buttonBar;
    },

    generateButton(className, label) {
        // Button-Element erstellen
        const button = document.createElement('button');
        button.className = className;
        button.textContent = label;
        button.addEventListener('click', () => this.newGame(className)); // Event Listener hinzufügen
        return button;
    },

    generateFooter() {
        // Footer-Element erstellen
        const footer = document.createElement('footer');
        footer.innerHTML = `
            <div class="footer">
                <p>2024 by Kevin Böhmisch</p>
            </div>
        `;
        return footer;
    },

    async newGame(size) {
        const gameModes = [
            { type: 'small', rows: 9, cols: 9, mines: 10 },
            { type: 'medium', rows: 16, cols: 16, mines: 40 },
            { type: 'large', rows: 24, cols: 24, mines: 150 }
        ];

        let selectedMode;
        for (let mode of gameModes) {
            if (mode.type === size) {
                selectedMode = mode;
                break;
            }
        }

        if (selectedMode) {
            await this.generateFields(selectedMode.rows, selectedMode.cols, selectedMode.mines, selectedMode.type);
        }
    },

    async generateFields(rows, cols, mines, size) {
        const playfield = document.querySelector('#playfield');
        playfield.innerHTML = ''; // Playfield leeren

        const $ = (size === 'small') ? 9 : (size === 'medium') ? 16 : (size === 'large') ? 24 : 9;

        // Bestehendes style-Element entfernen, wenn vorhanden
        let style = document.querySelector('#dynamic-style');
        if (style) {
            style.remove();
        }

        // Neues style-Element erstellen
        style = document.createElement('style');
        style.id = 'dynamic-style';
        style.innerHTML = `
            .cell {
                width: calc(100% / ${$});
                height: calc(100% / ${$});
                box-sizing: border-box; /* Border und Padding werden in die Größe einbezogen */
            }
        `;
        document.head.appendChild(style);

        for (let i = 0; i < rows; i++) {
            for (let j = 0; j < cols; j++) {
                const cell = this.generateCell(i, j);
                playfield.appendChild(cell);
            }
        }

        // Spiellogik initialisieren
        const userid = 'keboit00';
        const initResponse = await remoteLogic.init(userid, rows, mines);
        console.log('Game initialized with token:', initResponse.token);

        // Die Anzahl der Minen können Sie hier verwenden, um die Minen zu platzieren (logisch)
        console.log(`Generating field with ${rows} rows, ${cols} columns, and ${mines} mines.`);
    },

    generateCell(row, col) {
        const cell = document.createElement('div');
        cell.classList.add('cell', 'covered_class');
        cell.dataset.x = col;
        cell.dataset.y = row;

        cell.addEventListener('click', (event) => this.cellClicked(event));
        cell.addEventListener('contextmenu', (event) => this.cellRightClicked(event));

        cell.addEventListener('touchstart', (event) => this.touchStart(event));
        cell.addEventListener('touchend', (event) => this.touchEnd(event));

        return cell;
    },

    touchStart(event) {
        event.preventDefault();
        this.touchStartTime = new Date().getTime();
    },

    touchEnd(event) {
        event.preventDefault();
        const touchEndTime = new Date().getTime();
        const touchDuration = touchEndTime - this.touchStartTime;

        const cell = event.target;
        const x = cell.dataset.x;
        const y = cell.dataset.y;

        if (touchDuration > 500) {
            this.cellRightClicked(event);
        } else {
            this.cellClicked(event);
        }
    },

    async cellClicked(event) {
        event.preventDefault();
        const cell = event.target;
        const x = parseInt(cell.dataset.x, 10);
        const y = parseInt(cell.dataset.y, 10);
        console.log(`Cell clicked at (${x}, ${y})`);

        // Spiellogik aufrufen
        const result = await remoteLogic.sweep(x, y);

        // Klasse covered_class entfernen und revealed hinzufügen
        cell.classList.remove('covered_class');
        cell.classList.add('revealed');

        if (result.minehit) {
            console.log('You hit a mine! Game over.');
            console.log('Mines are at:', result.mines);
            cell.classList.add('cell_symbol_m', 'cell_symbol_mine_clicked'); // Mine anzeigen und rot hinterlegen
            this.revealAllMines(result.mines); // Alle Minen anzeigen
            this.showOverlay(false); // Spielende Overlay anzeigen
        } else {
            if (result.userwins) {
                console.log('You won the game!');
                this.showOverlay(true); // Spielgewinn Overlay anzeigen
            } else {
                if (result.minesAround !== undefined) {
                    console.log(`Mines around: ${result.minesAround}`);
                    cell.classList.add(`cell_symbol_${result.minesAround}`); // Minenanzahl anzeigen
                }
                if (result.emptyCells !== undefined) {
                    console.log('Empty cells:', result.emptyCells);
                    result.emptyCells.forEach(cellData => {
                        const emptyX = cellData.x;
                        const emptyY = cellData.y;
                        const emptyCell = document.querySelector(`[data-x="${emptyX}"][data-y="${emptyY}"]`);
                        emptyCell.classList.remove('covered_class');
                        emptyCell.classList.add('revealed');

                        // Zeigt die Anzahl der Minen in der Nähe des leeren Feldes an
                        const minesAround = cellData.minesAround;
                        if (minesAround > 0) {
                            emptyCell.classList.add(`cell_symbol_${minesAround}`);
                        }
                    });
                }
            }
        }
    },

    cellRightClicked(event) {
        event.preventDefault();
        const cell = event.target;
        const x = parseInt(cell.dataset.x, 10);
        const y = parseInt(cell.dataset.y, 10);
        console.log(`Cell right-clicked at (${x}, ${y})`);

        // Flag setzen oder entfernen
        if (cell.classList.contains('cell_symbol_f')) {
            cell.classList.remove('cell_symbol_f');
        } else {
            cell.classList.add('cell_symbol_f');
        }
    },

    revealAllMines(mines) {
        if (Array.isArray(mines)) {
            mines.forEach(mine => {
                const { x, y } = mine;
                const mineCell = document.querySelector(`[data-x="${x}"][data-y="${y}"]`);
                mineCell.classList.remove('covered_class');
                mineCell.classList.add('revealed', 'cell_symbol_m');
            });
        } else {
            console.error('Mines data is not in the expected format:', mines);
        }
    },

    showOverlay(won) {
        const overlay = document.createElement('div');
        overlay.classList.add('overlay');

        const textHolder = document.createElement('div');
        textHolder.classList.add('textholder');
        textHolder.innerText = won ? 'You Win!' : 'You Lose!';
        overlay.appendChild(textHolder);

        // Overlay auf das Playfield setzen
        const playfield = document.querySelector('#playfield');
        playfield.style.position = 'relative';
        playfield.appendChild(overlay);
    }
};

window.addEventListener('load', async function() {
    await minesweeper.init();
});
