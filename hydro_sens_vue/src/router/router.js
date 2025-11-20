import { createRouter, createWebHistory } from 'vue-router';
import Home from '../views/Home.vue';
import Login from '../views/Login.vue';
// import Register from '../views/Register.vue';
import axios from 'axios';
const routes = [
    { path: '/', name: 'home', component: Home },
    { path: '/login', name: 'login', component: Login },
    // { path: '/register', name: 'register', component: Register }
];

const router = createRouter({
    history: createWebHistory(),
    routes
});

async function check_token() {
    const token = localStorage.getItem('token');
    if (!token) return false;

    try {
        const header = { Authorization: `Bearer ${token}` };
        const response = await axios.get('http://localhost:3000/user/profile', { headers: header });

        return response.data.status === 'success';
    } catch (error) {
        console.log('error at router.js check_token:', error);
        return false;
    }
}

//middleware check login nav guard
router.beforeEach(async (to, from, next) => {

    // if (to.name === 'register') {
    //     next();
    //     return;
    // }

    if (to.name === 'login') {
        next();
        return;
    }

    const isValidToken = await check_token();
    
    if (!isValidToken) {
        next('/login');
        return;
    }

    next();
});

export default router;