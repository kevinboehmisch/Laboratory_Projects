import { createRouter, createWebHistory } from 'vue-router';
import HomeView from '../views/HomeView.vue';
import VerlaufView from '../views/VerlaufView.vue';
import UebungView from '../views/UebungView.vue';

const routes = [
    { path: '/', name: 'Home', component: HomeView },
    { path: '/verlauf', name: 'Verlauf', component: VerlaufView }, 
    { path: '/uebungen', name: 'Uebungen', component: UebungView }, 
  ];
  

const router = createRouter({
  history: createWebHistory(),
  routes,
});

export default router;
