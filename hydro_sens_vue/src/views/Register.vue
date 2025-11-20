<script setup>
import { useRouter } from 'vue-router'
import { ref } from 'vue'
import axios from 'axios'
const username = ref('')
const password = ref('')
const password_confirm = ref('')
const product_key = ref('')
const router = useRouter()

function handleSubmit() {
    const body = {
        username: username.value,
        password: password.value,
        product_key: product_key.value
    }

    if (password.value !== password_confirm.value) {
        alert('Passwords do not match')
        return
    }

    axios.post('http://localhost:3000/user/register', body).then(response => {
        if (response.data.status === 'success') {
            router.push('/login')
        } else {
            console.error('register fail:', response.data.message)
        }
    }).catch(error => {
        console.error('register failed:', error)
    })
}
</script>

<template>
    <main class="page-shell">
        <section class="auth-card">
            <h1>Register</h1>
            <form @submit.prevent="handleSubmit">
                <div>
                    <label for="register-username">Username:</label>
                    <input id="register-username" type="text" v-model="username" autocomplete="username" />
                </div>
                
                <div>
                    <label for="register-password">Password:</label>
                    <input id="register-password" type="password" v-model="password" autocomplete="current-password" />
                </div>
                
                <div>
                    <label for="register-password-confirm">Confirm Password:</label>
                    <input id="register-password-confirm" type="password" v-model="password_confirm" autocomplete="current-password" />
                </div>
                
                <div>
                    <label for="register-product-key">Product Key:</label>
                    <input id="register-product-key" type="text" v-model="product_key" autocomplete="current-product-key" />
                </div>
                <button type="submit">Register</button>
            </form>
        </section>
    </main>
</template>
