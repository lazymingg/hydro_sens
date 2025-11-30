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

// khi moi vao trang
onMounted(() => {
    update_data();
    polling_interval = setInterval(update_data, 2000); 
});

// khi thoat trang tat interval
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
            <h1>Interactive Page</h1>
            <div class="dashboard-1">
                
                <div class="info-card">
                    <div class="card-title">Mức Nước</div>
                    <div class="card-content">
                        <div class="card-description">Mức nước hiện tại</div>
                        <div class="card-value">{{ water_level }}</div>
                    </div>
                </div>
                
                <div class="info-card">
                    <div class="card-title">Nhiệt Độ</div>
                    <div class="card-content">
                        <div class="card-description">nhiệt độ hiện tại</div>
                        <div class="card-value">{{ temperature }}°C</div>
                    </div>
                </div>
                
                <div class="info-card">
                    <div class="card-title">Chỉ Số TDS</div>
                    <div class="card-content">
                        <div class="card-description">chỉ số TDS hiện tại</div>
                        <div class="card-value">{{ tds }} ppm</div>
                    </div>
                </div>


            </div>
            <div class="dashboard-2">
                
                <div class="info-card">
                    <div class="card-title">Cho ăn</div>
                    <div class="card-description">bấm để nhả thức ăn</div>
                    <!-- <div class="card-value">{{ water_level }}</div> -->
                </div>
                
                <div class="info-card">
                    <div class="card-title">Bật đèn uv</div>
                    <div class="card-description">bấm để mở đèn uv</div>
                    <!-- <div class="card-value">{{ temperature }}°C</div> -->
                </div>
                
                <!-- <div class="info-card">
                    <div class="card-title">Chỉ Số TDS</div>
                    <div class="card-description">chỉ số TDS hiện tại</div>
                    <div class="card-value">{{ tds }} ppm</div>
                </div> -->


            </div>
            <!-- <div class="raw-data">
                <h2>Dữ Liệu Thô</h2>
                <div>Mực nước: <strong>{{ water_level }}</strong></div>
                <div>Nhiệt độ: <strong>{{ temperature }}°C</strong></div>
                <div>Chỉ số TDS: <strong>{{ tds }} ppm</strong></div>
            </div> -->
        </section>
    </main>
</template>
<!-- :root {
  --color-background: var(--vt-c-white);
  --color-background-soft: var(--vt-c-white-soft);
  --color-background-mute: var(--vt-c-white-mute);

  --color-border: var(--vt-c-divider-light-2);
  --color-border-hover: var(--vt-c-divider-light-1);

  --color-heading: var(--vt-c-text-light-1);
  --color-text: var(--vt-c-text-light-1);

  --section-gap: 10rem;
  font-size: clamp(14px, 1.2vw + 0.2rem, 18px);
  line-height: 1.5;

  --space-1: 0.5rem;
  --space-2: 1rem;
  --space-3: 1.5rem;
  --radius: 0.5rem;
  --shadow-soft: 0 0.75rem 2rem rgba(0, 0, 0, 0.08);
} -->

<style scoped>
.dashboard-1, .dashboard-2{
    width: 100%;
    padding: var(--space-2);
    /* background-color: var(--color-background); */
    display: flex;
    gap: 1rem;
    flex-wrap: wrap;
    justify-content: center;
    border: 1px solid var(--color-border);
}
.card-title {
    font-size: 1.2rem;
    font-weight: bold;
    margin-bottom: 5px;
} 

.info-card {
    background-color: var(--color-background-soft);
    border: 1px solid var(--color-border);
    border-radius: 0.3rem;
    padding: var(--space-2);
    width: 80%;
    display: flex;
    gap : 10px;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}
.card-content {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: center;
    gap: 10px;
}
.panel {
    display: flex;
    flex-direction: column;
    gap: 30px;
    align-items: center;
}

@media (min-width: 720px) {
    .info-card {
        width: 30%;
    }
}
</style>
