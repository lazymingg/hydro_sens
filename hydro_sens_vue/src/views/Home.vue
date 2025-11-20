<script setup>
import { reactive, onMounted, onUnmounted, ref } from 'vue';
import axios from 'axios';

const water_level = ref(0);
const temperature = ref(0);
const tds = ref(0);

let polling_interval = null;

async function update_data() {
    const token = localStorage.getItem('token');
    if (!token) {
        console.warn("khong thay token");
        return;
    }

    try {
        const response = await axios.get('http://localhost:3000/user/hydro_sens_data', { 
            headers: {'Authorization': `Bearer ${token}`}
        });

        if (response.data.status === 'success') {
            const data = response.data.data;
            water_level.value = data.water_level;
            temperature.value = data.temperature;
            tds.value = data.tds;
        }
    } catch (error) {
        console.error('error:', error);
    }
}

onMounted(() => {
    update_data();
    polling_interval = setInterval(update_data, 2000); 
});

onUnmounted(() => {
    if (polling_interval) {
        clearInterval(polling_interval);
        console.log("Đã hủy vòng lặp update data");
    }
});



</script>

<template>
    <main class="page-shell">
        <section class="panel">
            <h1>Home Page</h1>
            <div class="dashboard">
                <div>Mực nước: <strong>{{ water_level }}</strong></div>
                <div>Nhiệt độ: <strong>{{ temperature }}°C</strong></div>
                <div>Chỉ số TDS: <strong>{{ tds }} ppm</strong></div>
            </div>
        </section>
    </main>
</template>

<style scoped>
.dashboard {
    display: grid;
    gap: var(--space-1);
    margin-top: var(--space-2);
    font-size: 1.1rem;
} 
</style>
