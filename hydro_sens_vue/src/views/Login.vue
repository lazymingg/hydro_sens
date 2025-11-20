<script setup>
import { useRouter } from 'vue-router'
import { ref } from 'vue'
import axios from 'axios'
const username = ref('')
const password = ref('')
const password_confirm = ref('')
const product_key = ref('')
const router = useRouter()

function handle_login_submit() {
  const body = {
    username: username.value,
    password: password.value
  }

  axios.post('http://localhost:3000/user/login', body).then(response => {
    if (response.data.status === 'success') {
      const token = response.data.data.token
      localStorage.setItem('token', token)
      router.push('/')
    } else {
      alert('login failed: ' + response.data.message)
      console.error('login fail:', response.data.message)
    }
  }).catch(error => {
    console.error('Login failed:', error)
  })
}

function handle_register_submit() {
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
      alert('register successful')
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
    <div class="auth-layout">
      <section class="auth-card">
        <h1>Login</h1>
        <form @submit.prevent="handle_login_submit">
          <div>
            <label for="login-username">Username:</label>
            <input id="login-username" type="text" v-model="username" autocomplete="username" />
          </div>

          <div>
            <label for="login-password">Password:</label>
            <input id="login-password" type="password" v-model="password" autocomplete="current-password" />
          </div>
          <button type="submit">Login</button>
        </form>
      </section>

      <section class="auth-card">
        <h1>Register</h1>
        <form @submit.prevent="handle_register_submit">
          <div>
            <label for="register-username">Username:</label>
            <input id="register-username" type="text" v-model="username" autocomplete="username" />
          </div>

          <div>
            <label for="register-password">Password:</label>
            <input id="register-password" type="password" v-model="password" autocomplete="current-password" />
          </div>

          <div>
            <label for="password_confirm">Confirm Password:</label>
            <input id="password_confirm" type="password" v-model="password_confirm" autocomplete="current-password" />
          </div>

          <div>
            <label for="product_key">Product Key:</label>
            <input id="product_key" type="text" v-model="product_key" autocomplete="current-product-key" />
          </div>
          <button type="submit">Register</button>
        </form>
      </section>
    </div>
  </main>
</template>

<style scoped>

.page-shell {
  min-height: 100vh;
  display: flex;
  align-items: center;
  justify-content: center;
}

.auth-layout {
  display: flex;
  flex-wrap: wrap;
  gap: var(--space-2);
  justify-content: center;
  flex-direction: row;
}

.auth-card {
  width: 20rem;
  background: var(--color-background);
  border: 1px solid var(--color-border);
  border-radius: var(--radius);
  padding: var(--space-3);
}

.auth-card h1 {
  margin-bottom: var(--space-2);
}


</style>