import { createRouter, createWebHistory } from 'vue-router';
import Home from '../views/Home.vue';
import Login from '../views/Login.vue';

const routes = [
    { path: '/', name: 'home', component: Home },
    { path: '/login', name: 'login', component: Login }
];

const router = createRouter({
    history: createWebHistory(),
    routes
});


//middleware check login nav guard
router.beforeEach((to, from, next) => {
    const token = localStorage.getItem('token');
    const tokenValid = isTokenValid(token);
    console.log('=== ROUTER DEBUG ===');
    console.log('Going to:', to.name, to.path);
    console.log('Token exists:', !!token);
    console.log('Token valid:', tokenValid);
    
    if (!tokenValid) {
        // Clear bad token so we don't keep looping with stale data
        localStorage.removeItem('token');
        if (to.name !== 'login') {
            console.log('Token invalid or missing, redirecting to login');
            next('/login');
            return;
        }
    } else if (to.name === 'login') {
        console.log('Has valid token, redirecting to home');
        next('/');
        return;
    }
    
    console.log('Proceeding to route');
    next();
});

export default router;
