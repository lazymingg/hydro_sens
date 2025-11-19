const express = require('express');
const router = express.Router();
const sqlite3 = require('sqlite3').verbose();
const auth = require('../middleware/auth')
const respond_helper = require('../utils/respond_helper')
const jwt_helper = require('../utils/jwt')
const db = new sqlite3.Database("./hydro_sens.db", (err) => {
    if (err) {
        console.error('eror open db file make sure run db_init.js')
    }
})


//login
router.post("/login", (req, res) => {
    const { username, password } = req.body;

    db.get(
        "SELECT * FROM users WHERE username = ? AND password = ? LIMIT 1",
        [username, password],
        (err, user) => {

            if (err) {
                return respond_helper.error(res, {}, "db error" + err.message);
            }

            if (!user) {
                return respond_helper.error(res, {}, "invalid username pssw");
            }

            const token = jwt_helper.sign({ username: user.username });

            return respond_helper.success(res, { user: user, token: token }, "login success");
        }
    );
});

//register
router.post("/register", (req, res) => {
    const { username, password, product_key } = req.body;

    if (!username || !password || !product_key) {
        return respond_helper.error(res, {}, "missing username or password or product_key");
    }

    db.run(
        "INSERT INTO users (username, password, product_key) VALUES (?, ?, ?)",
        [username, password, product_key],

        function (err) {
            if (err) {
                return respond_helper.error(res, {}, "register failded" + err.message);
            }
            return respond_helper.success(res, {}, "register success");
        }
    );
});

router.get("/profile", auth, (req, res) => {
    const username = req.user.username;
    if (!username) {
        return respond_helper.error(res, {}, "you must login first");
    }

    else {
        db.get(
            "SELECT username, product_key FROM users WHERE username = ? LIMIT 1", [username],
            (err, user) => {
                if (err || !user) {
                    return respond_helper.error(res, {}, "invalid user");
                }
                return respond_helper.success(res, { user: user }, "here your profile");
            }
        );
    }
});


module.exports = router;