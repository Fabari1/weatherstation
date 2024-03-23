<template>
    <v-container class="bg-surface mb-6" align="center">

        <v-sheet class="pa-2 ma-2" color="surface" rounded="xl" :width="1050" align="center">
        <v-col cols="10">
        <v-row :max-width="1000">
            <v-col align="start" no-gutters>
                
                <v-card class="mx-auto" :width="600" :height="300" rounded="xl" align="center" justify="center" title="Temperature">
            
                    <v-row justify="start">
                        <v-col align="center">
                            <span class="text-h3"> {{ temperature }} </span>
                        </v-col>
                        <v-col>
                            <VImg height="80" class="mb-5" :src="`https://openweathermap.org/img/wn/${isUmbrella}d@2x.png`" />
                        </v-col>
                    </v-row>
                    <p class="font-italic">{{ forecastNotes }}</p><br>
                    <v-btn class="button"  @click="convertTo();" color="surface-variant"  variant="outlined" > Convert to {{ units }}
                         </v-btn>
                </v-card>
            </v-col>
           <v-row>
            <v-col align="end">
                    <v-sheet   :width="210" subtitle="Weather Conditions">
                        <v-card-item> 
                            <v-list-item
                                density="compact"
                                prepend-icon="mdi-thermometer-high"
                                >
                                <p class="text-h7">Feels Like</p>
                                <span class="text-h6"> {{ heatindex }} </span>
                       
                            </v-list-item><br>
                            <v-list-item
                                density="compact"
                                prepend-icon="mdi-water-outline"
                                >
                                <p class="text-h7">Humidity</p>
                                <span class="text-h6"> {{ humidity }} </span>
                            </v-list-item><br>
                            <v-list-item
                                density="compact"
                                prepend-icon="mdi-weather-windy"
                                >
                                <p class="text-h7">Air Pressure</p>
                                <span class="text-h6"> {{ airpressure }} </span>
                            </v-list-item><br>
                        </v-card-item>
                    </v-sheet>
            
                </v-col>
                <v-row>
                  
                </v-row>
        </v-row>
        <v-col cols="12">
            <figure class="highcharts-figure">
                <div id="container"></div>

            </figure>
            
        </v-col>
        </v-row>
        <v-row  justify="start">
            <v-col cols="9">
                <figure class="highcharts-figure">
                    <div id="container1"></div>
                </figure>
                
            </v-col>
            <v-col cols="3">
                <v-card rounded="xl" subtitle="Soil Moisture Percentage" :width="280" :height="380" >
                <v-progress-circular  :rotate="360" :model-value="moist" :size="250" :width="6" color="teal">
                    <template v-slot:default> {{ moist }} % </template>
                </v-progress-circular>
                </v-card>
            </v-col>
        </v-row>
        </v-col>
    </v-sheet>
    </v-container> 
</template>

<script setup>
/** JAVASCRIPT HERE */

// IMPORTS
// Highcharts, Load the exporting module and Initialize exporting module.
import Highcharts from 'highcharts';
import more from 'highcharts/highcharts-more';
import Exporting from 'highcharts/modules/exporting';
Exporting(Highcharts);
more(Highcharts);


import { useMqttStore } from '@/store/mqttStore'; // Import Mqtt Store
// import WeatherWidget from '@/components/WeatherWidget.vue'
import { storeToRefs } from "pinia";
import { ref,reactive,watch ,onMounted,onBeforeUnmount,computed } from "vue";  
import { useRoute ,useRouter } from "vue-router";
 
 
// VARIABLES
const router      = useRouter();
const route       = useRoute();  
const Mqtt = useMqttStore();
const { payload, payloadTopic } = storeToRefs(Mqtt);
const mqtt = ref(null);
const host = ref("dbs.msjrealtms.com"); // Host Name or IP address
const port = ref(9002); // Port number
const points = ref(10); // Specify the quantity of points to be shown on the live graph simultaneously.
const shift = ref(false); // Delete a point from the left side and append a new point to the right side of the graph.
const isUmbrella = ref("02"); // Weather icon
const forecastNotes = ref("Weather is normal"); // Weather forecast notes
const temperature = computed(()=>{
    if(!!payload.value){
        if(isCelsius){
            return `${payload.value.temperature.toFixed(2)} °C`;
        }else{
            return `${convertToFahrenheit(payload.value.temperature).toFixed(2)} °F`;
        }
    }
});
const heatindex = computed(()=>{
    if(!!payload.value){
        if(isCelsius){
            return `${payload.value.heatindex.toFixed(2)} °C`;
        }else{
            return `${convertToFahrenheit(payload.value.heatindex).toFixed(2)} °F`;
        }
    }
});
const humidity = computed(()=>{
    if(!!payload.value){
    return `${payload.value.humidity.toFixed(2)} %`;
    }
});
const airpressure = computed(()=>{
    if(!!payload.value){
    return `${payload.value.pressure.toFixed(2)} hPa`;
    }
});
const units = ref("Fahrenheit"); // Temperature units
const tempChart = ref(null); // Chart object
const HiChart = ref(null); // Chart object
let isCelsius = true; // Temperature units
let moist = ref(0); // soil moisture


const CreateCharts = async () => {
// TEMPERATURE CHART
    tempChart.value = Highcharts.chart('container', {
    chart: { zoomType: 'x' },
    title: { text: 'Temperature Analysis and Heat Index (Live)', align: 'left' },
    yAxis: {
    title: { text: '°C', style:{color:'#000000'}},
    labels: { format:'{value} °C' }
    },
    xAxis: {
    type: 'datetime',
    title: { text: 'Time', style:{color:'#000000'} },
    },
    tooltip: { shared:true, },
    series: [
    {
    name: 'Temperature',
    type: 'spline',
    data: [],
    turboThreshold: 0,
    color: Highcharts.getOptions().colors[8]
    },
    {
    name: 'Heat Index',
    type: 'spline',
    data: [],
    turboThreshold: 0,
    color: Highcharts.getOptions().colors[6]
    } ],
    });
    
    HiChart.value = Highcharts.chart('container1', {
    chart: { zoomType: 'x' },
    title: { text: 'Humidity Analysis (Live)', align: 'left' },
    yAxis: {
    title: { text: '%' , style:{color:'#000000'}},
    labels: { format: '{value} %' }
    },
    xAxis: {
    type: 'datetime',
    title: { text: '', style:{color:'#000000'} },
    },
    tooltip: { shared:true, },
    series: [
    {
    name: 'Humidity',
    type: 'spline',
    data: [],
    turboThreshold: 0,
    color: Highcharts.getOptions().colors[14]
    } ],
    });
    

};



// FUNCTIONS
onMounted(()=>{
    // THIS FUNCTION IS CALLED AFTER THIS COMPONENT HAS BEEN MOUNTED
    CreateCharts();

    Mqtt.connect(); // Connect to Broker located on the backend
    setTimeout( ()=>{
    // Subscribe to each topic
    Mqtt.subscribe("620154701");
    Mqtt.subscribe("620154701_pub");}, 3000);
});


onBeforeUnmount(()=>{
    // THIS FUNCTION IS CALLED RIGHT BEFORE THIS COMPONENT IS UNMOUNTED
    Mqtt.unsubcribeAll();
});



watch(payload,(data)=> {
        if(points.value > 0){ points.value -- ; }
        else{ shift.value = true; }

        
     moist.value = parseFloat(data.soilmoisture);

   if(isCelsius){

        tempChart.value.series[0].addPoint({y:parseFloat(data.temperature.toFixed(2)) ,x: (data.timestamp-18000) * 1000 },
        true, shift.value);
        tempChart.value.series[1].addPoint({y:parseFloat(data.heatindex.toFixed(2)) ,x: (data.timestamp-18000) * 1000 },
        true, shift.value);
        HiChart.value.series[0].addPoint({y:parseFloat(data.humidity.toFixed(2)) ,x: (data.timestamp-18000)* 1000 },
        true, shift.value);
    }else{
        tempChart.value.series[0].addPoint({y:convertToFahrenheit(parseFloat(data.temperature.toFixed(2))) ,x: (data.timestamp-18000) * 1000 },
        true, shift.value);
        tempChart.value.series[1].addPoint({y:convertToFahrenheit(parseFloat(data.heatindex.toFixed(2))) ,x: (data.timestamp-18000) * 1000 },
        true, shift.value);
        HiChart.value.series[0].addPoint({y:parseFloat(data.humidity.toFixed(2)) ,x: (data.timestamp-18000)* 1000 },    
        true, shift.value);
}
if ( data.temperature > 20 && data.temperature < 25 && data.humidity > 50 && data.humidity < 70){
    console.log("Temperature and Humidity are within the normal range");
    forecastNotes.value = "Clouds a cover di sky today, bringing a cool breeze and a break from di sun's glare.";
    isUmbrella.value = "02";}
if ( data.temperature > 25  || data.humidity > 70 && data.humidity < 90){
    console.log("Temperature and Humidity are above the normal range");
    forecastNotes.value = "Today's forecast seh di sun a go shine bright, inviting everybody fi soak up di warmth and vibes.";
    isUmbrella.value = "01";}
if ( data.temperature > 15 && data.temperature < 20  || data.humidity > 70 && data.humidity < 90){
    console.log("Temperature and Humidity are below the normal range");
    forecastNotes.value = "Rain a go fall today, so mek sure yuh grab yuh umbrella and stay dry as yuh move about.";
    isUmbrella.value = "04";}
});

const convertToFahrenheit = (celsius) => {
    return (celsius * 9/5) + 32;
};


function convertTo() {
    // Code to read passcode here
    isCelsius = !isCelsius;

    if(isCelsius){
        units.value = "Fahrenheit";
        tempChart.value.yAxis[0].update({title: { text: '°C' , style:{color:'#000000'}}});
        tempChart.value.yAxis[0].update({labels: { format:'{value} °C' }});
    }else{
        units.value = "Celsius";
        tempChart.value.yAxis[0].update({title: { text: '°F' , style:{color:'#000000'}}});
        tempChart.value.yAxis[0].update({labels: { format:'{value} °F' }});
    }
}

</script>


<style scoped>
/** CSS STYLE HERE */

.mb-5 {
    display: flex;
    padding: 0;
    margin: 0;
}
Figure {
border: 2px solid black;
}

.font-italic {
    font-style: italic;

}

.mx-auto {
    display: block;
    background: linear-gradient(45deg, rgb(255, 124, 30), rgb(242, 234, 228));
    padding:"25px 50px 75px 100px;"
}



</style>
  