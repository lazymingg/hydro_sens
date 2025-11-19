const jwt_helper = require('../utils/jwt');
const respond_helper = require('../utils/respond_helper')

function auth_middleware(req, res, next) {
    const header = req.headers['authorization'];
    
    if (!header) {
        return respond_helper.error(res, {}, 'no token in header')        
    }

    // tach dau cach lay phan tu thu 2 la token
    const token = header.split(" ")[1];

    try {
        const decode = jwt_helper.verify(token);
        req.user = decode
        next();
    }
    catch (err)
    {
        return respond_helper.error(res, {}, 'invalid token')
    }

}

module.exports = auth_middleware;