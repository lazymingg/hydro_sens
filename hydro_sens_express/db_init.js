// file that create the initial database schema with username,pssw, key
const sqlite3 = require('sqlite3').verbose();

const db = new sqlite3.Database('hydro_sens.db', (err) => {
    if (err) {
        console.error('error when create db', err.message);
    } else {
        console.log('successfully created db');
    }
});

// db don gian gom username, pass va productkey
db.serialize(() => {
    db.run('CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT, product_key TEXT)', (err) => {
        if (err) {
            console.error('error when creating users table', err.message);
        } else {
            console.log('users table created successfully');
        }
    });

    // them mot so user mac dinh
    db.run('INSERT INTO users (username, password, product_key) VALUES (?, ?, ?)', ['admin', 'admin'], (err) => {
        if (err) {
            console.error('error when inserting default user', err.message);
        } else {
            console.log('default user inserted successfully');
        }
    });
});

//dong db
db.close((err) => {
    if (err) {
        console.error('error when closing db', err.message);
    } else {
        console.log('database connection closed');
    }
});

