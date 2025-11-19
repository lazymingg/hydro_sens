<script setup>
    import { useRouter } from 'vue-router'
    import { ref } from 'vue'
    import axios from 'axios'
    const username = ref('')
    const password = ref('')
    const router = useRouter()
    function handleSubmit() {
        const body = {
            username: username.value,
            password: password.value
        }
        axios.post('http://localhost:3000/user/login', body).then(response => {
            if (response.data.status === 'success') {
                const token = response.data.data.token
                //test
                console.log('Received token:', response.data.data.token)
                //set token to localStorage
                localStorage.setItem('token', token)
                console.log('login successl, token saved')
                
                //redirect to home page
                router.push('/')
            } else {
                console.error('login fail:', response.data.message)
            }}).catch(error => {
            console.error('Login failed:', error)
        })
    }
</script>

<template>
    <h1>Login</h1>
    <form @submit.prevent="handleSubmit">
        <div>
            <label for="username">Username:</label>
            <input id="username" type="text" v-model="username" autocomplete="username" />
        </div>

        <div>
            <label for="password">Password:</label>
            <input id="password" type="password" v-model="password" autocomplete="current-password" />
        </div>
        <button type="submit">Login</button>
    </form>
</template>

<style scoped></style>