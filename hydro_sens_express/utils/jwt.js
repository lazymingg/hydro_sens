const jwt = require('jsonwebtoken');

const SECRET = "s0_y0u_w4nt_t0_h4ck_l4zym1ng_?"

function sign(payload, expried = '2d') {
    return jwt.sign(payload, SECRET, {expiresIn: expried})
}

function verify(token) {
    return jwt.verify(token, SECRET)
}

module.exports = {
    sign,
    verify
}