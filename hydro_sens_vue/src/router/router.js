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
    console.log('=== ROUTER DEBUG ===');
    console.log('Going to:', to.name, to.path);
    console.log('Token exists:', !!token);
    console.log('Token value:', token);
    
    if (!token && to.name !== 'login') {
        console.log('No token, redirecting to login');
        next('/login');
        return;
    }

    if (token && to.name === 'login') {
        console.log('Has token, redirecting to home');
        next('/');
        return;
    }
    
    console.log('Proceeding to route');
    next();
});

export default router;