<template>
    <v-container class="bg-surface mb-6" align="center">

        <v-sheet class="pb-2 mb-2" color="surface" rounded="xl"  align="center">
                <v-row :max-width="1000">
                    <v-col align="start" cols="8" no-gutters>
                        
                        <v-card class="mx-auto" :width="600" :height="300" rounded="xl" align="center" justify="center" title="Temperature">
                    
                            <v-row justify="start">
                                <v-col align="center">
                                    <span class="text-h2"> {{ temperature }} </span>
                                </v-col>
                                <v-col>
                                    <VImg height="80" class="mb-10" :src="`https://openweathermap.org/img/wn/${isUmbrella}d@2x.png`" />
                                </v-col>
                            </v-row>
                            <p class="ma-5">{{ forecastNotes }}</p><br>
                        </v-card>
                        <br>
                        <v-sheet align="center" >
                            <v-row class="w-50">
                       
                            <v-autocomplete
                            
                            clearable
                            chips
                            label="Convert Units to"
                            :items="[isCelsius ? 'Fahrenheit' : 'Celsius', isPressure ? 'Millimetre of Mercury' : 'Hectopascal', isAltitude ? 'Feet' : 'Metres']"
                            multiple
                            v-model="selected"
                            
                            variant="solo-filled"
                            ></v-autocomplete>
                            <v-btn
                                class="ma-2"
                                variant="contained"
                                @click="convertTo(); hasSaved = true"
                                prepend-icon="mdi-swap-horizontal"
                                
                                >
                                Convert
                            </v-btn>
                       
                        </v-row>
                    </v-sheet>
                
                    </v-col>
            <v-col  cols="4">
                    <v-sheet class="ml-10"  :width="210" subtitle="Weather Conditions">
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
                            <v-list-item
                                density="compact"
                                prepend-icon="mdi-transfer-up"
                                >
                                <p class="text-h7">Altitude</p>
                                <span class="text-h6"> {{ altitude }} </span>
                            </v-list-item><br>
                        </v-card-item>
                    </v-sheet>
                    
            </v-col>
                
            </v-row>
        <v-row>
        <v-col cols="12">
            <figure class="highcharts-figure">
                <div id="container"></div>

            </figure>
            
        </v-col>
        </v-row>
        <v-row  justify="start">
            <v-col cols="12">
                <figure class="highcharts-figure">
                    <div id="container1"></div>
                </figure>
                
            </v-col>
        </v-row>
        <v-row  justify="start">
            <v-col cols="12">
                <figure class="highcharts-figure">
                    <div id="container94"></div>
                </figure>
                
            </v-col>
        </v-row>
        <v-row>
            <v-col cols="6">
                <figure class="highcharts-figure">
                    <div id="container6"></div>
                </figure>
            </v-col>
            <v-col cols="6">
                <figure class="highcharts-figure">
                    <div id="container5"></div>
                </figure>
            </v-col>
        </v-row>
       
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
const tempunits = ref("Fahrenheit"); // Temperature units
const airunits = ref("Hectopascal"); // Pressure units
const altunits = ref("Feet"); // Altitude units
const tempChart = ref(null); // Chart object
const HiChart = ref(null); // Chart object
const altChart = ref(null); // Chart object
const soilChart = ref(null); // Chart object
const heightChart = ref(null); // Chart object  
let isCelsius = true; // Temperature units
let isPressure = true; // Pressure units
let isAltitude = true; // Altitude units
const hasSaved = false // Save status
let moist = ref(10); // soil moisture
const forecastNotes = ref("Weather is normal"); // Weather forecast notes
const selected = ref([]); // Selected units


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
    if(isPressure){
    return `${payload.value.pressure.toFixed(2)} hPa`;
    }else{
        return `${convertToMercury(payload.value.pressure).toFixed(2)} mmHg`;
}}});

const altitude = computed(()=>{
    if(!!payload.value){
    if(isAltitude){
    return `${payload.value.altitude.toFixed(2)} m`;
    }else{
        return `${convertToFeet(payload.value.altitude).toFixed(2)} ft`;}
    }


});


const CreateCharts = async () => {
// TEMPERATURE CHART
    tempChart.value = Highcharts.chart('container', {
    chart: { zoomType: 'x' },
    title: { text: 'Temperature and Heat Index Analysis (Live)', align: 'left' },
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

    heightChart.value = Highcharts.chart('container94', {
    chart: { zoomType: 'x' },
    title: { text: 'Altitude Analysis (Live)', align: 'left' },
    yAxis: {
    title: { text: 'm' , style:{color:'#000000'}},
    labels: { format: '{value} m' }
    },
    xAxis: {
    type: 'datetime',
    title: { text: '', style:{color:'#000000'} },
    },
    tooltip: { shared:true, },
    series: [
    {
    name: 'Altitude',
    type: 'spline',
    data: [],
    turboThreshold: 0,
    color: Highcharts.getOptions().colors[8]
    } ],
    });

    altChart.value = Highcharts.chart('container5', {
    
        chart: {
            type: 'gauge',
            alignTicks: false,
            plotBackgroundColor: null,
            plotBackgroundImage: null,
            plotBorderWidth: 0,
            plotShadow: false
        },

        title: {
            text: 'Barometer Pressure (Live)',
        },

        pane: {
            startAngle: -150,
            endAngle: 150
        },

        yAxis: [{
            min: 950,
            max: 1050,
            lineColor: '#339',
            tickColor: '#339',
            minorTickColor: '#339',
            offset: -25,
            lineWidth: 2,
            labels: {
                distance: -20,
                rotation: 'auto'
            },
            tickLength: 5,
            minorTickLength: 5,
            endOnTick: false
        }, {
            min: 712,
            max: 787,
            tickPosition: 'outside',
            lineColor: '#933',
            lineWidth: 2,
            minorTickPosition: 'outside',
            tickColor: '#933',
            minorTickColor: '#933',
            tickLength: 5,
            minorTickLength: 5,
            labels: {
                distance: 12,
                rotation: 'auto'
            },
            offset: -20,
            endOnTick: false
        }],

        series: [{
            name: 'Pressure',
            data: [1000],
            dataLabels: {
                format: '<span style="color:#339">{y} hPa</span><br/>' +
                    '<span style="color:#933">{(multiply y 0.75):.0f} mmHg</span>',
                backgroundColor: {
                    linearGradient: {
                        x1: 0,
                        y1: 0,
                        x2: 0,
                        y2: 1
                    },
                    stops: [
                        [0, '#DDD'],
                        [1, '#FFF']
                    ]
                }
            },
            tooltip: {
                valueSuffix: 'hPa'
            }
        }]

        });

        soilChart.value = Highcharts.chart('container6', {
        title: { text: 'Soil Moisture (Live)', align: 'left' },// the value axis
        yAxis: {
        min: 0,
        max: 100,
        tickPixelInterval: 72,
        tickPosition: 'inside',
        tickColor: Highcharts.defaultOptions.chart.backgroundColor || '#FFFFFF',
        tickLength: 20,
        tickWidth: 2,
        minorTickInterval: null,
        labels: { distance: 20, style: { fontSize: '14px' } },
        lineWidth: 0,
        plotBands: [{ from: 0, to: 20, color: '#DF5353', thickness: 20 }, { from: 20, to: 60, color: '#DDDF0D', thickness: 20
        }, { from: 60, to: 100, color: '#55BF3B', thickness: 20 }]
        },
        tooltip: { shared:true, },
        pane: { startAngle: -90, endAngle: 89.9, background: null, center: ['50%', '75%'], size: '110%' },
        series: [{
        type:'gauge',
        name: 'Soil Moisture',
        data:[0],
        tooltip: { valueSuffix: ' %' },
        dataLabels: { format: '{y} %', borderWidth: 0, color: ( Highcharts.defaultOptions.title &&
        Highcharts.defaultOptions.title.style && Highcharts.defaultOptions.title.style.color ) || '#333333', style: { fontSize: '16px' }
        },
        dial: { radius: '80%', backgroundColor: 'gray', baseWidth: 12, baseLength: '0%', rearLength: '0%' },
        pivot: { backgroundColor: 'gray', radius: 6 }
        }]
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

        
    soilChart.value.series[0].points[0].update(data.soilmoisture);
    altChart.value.series[0].points[0].update(data.pressure);
    moist.value = data.altitude;

    
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
if(isAltitude){
    heightChart.value.series[0].addPoint({y:parseFloat(data.altitude.toFixed(2)) ,x: (data.timestamp-18000)* 1000 },
    true, shift.value);
}else{
    heightChart.value.series[0].addPoint({y:convertToFeet(parseFloat(data.altitude).toFixed(2)) , x: (data.timestamp-18000)* 1000 },
    true, shift.value);

}

if ( data.humidity>=65 && data.humidity<=70){
    console.log("Temperature and Humidity are within the normal range");
    forecastNotes.value = "Clouds a cover di sky today, bringing a cool breeze and a break from di sun's glare.";
    isUmbrella.value = "02";}
    if ( data.humidity>0 && data.humidity<65){
    console.log("Temperature and Humidity are above the normal range");
    forecastNotes.value = "Today's forecast seh di sun a go shine bright, inviting everybody fi soak up di warmth and vibes.";
    isUmbrella.value = "01";}
    if ( data.humidity>=70 && data.humidity<=100){
    console.log("Temperature and Humidity are below the normal range");
    forecastNotes.value = "Rain a go fall today, so mek sure yuh grab yuh umbrella and stay dry as yuh move about.";
    isUmbrella.value = "04";}

});

const convertToFahrenheit = (celsius) => {
    return (celsius * 9/5) + 32;
};

const convertToMercury = (pressure) => {
    return pressure * 0.750061561303;
};

const convertToFeet = (altitude) => {
    return altitude * 3.28084;
};

function convertTo() {
    // Code to read passcode here
    if(selected.value.includes("Fahrenheit")){
        isCelsius = false;
        tempunits.value = "Fahrenheit";
        tempChart.value.yAxis[0].update({title: { text: '°F' , style:{color:'#000000'}}});
        tempChart.value.yAxis[0].update({labels: { format:'{value} °F' }});
        
    }else if(selected.value.includes("Celsius")){
        isCelsius = true;
        tempunits.value = "Celsius";
        tempChart.value.yAxis[0].update({title: { text: '°C' , style:{color:'#000000'}}});
        tempChart.value.yAxis[0].update({labels: { format:'{value} °C' }});
    }

    if(selected.value.includes("Millimetre of Mercury")){
        isPressure = false;
        airunits.value = "Millimetre of Mercury";
    }else if(selected.value.includes("Hectopascal")){
        isPressure = true;
        airunits.value = "Hectopascal";
    }

    if(selected.value.includes("Feet")){
        isAltitude = false;
        altunits.value = "Feet";
        heightChart.value.yAxis[0].update({title: { text: 'ft' , style:{color:'#000000'}}});
        heightChart.value.yAxis[0].update({labels: { format:'{value} ft' }});
    }else if(selected.value.includes("Metres")){
        isAltitude = true;
        altunits.value = "Metres";
        heightChart.value.yAxis[0].update({title: { text: 'm' , style:{color:'#000000'}}});
        heightChart.value.yAxis[0].update({labels: { format:'{value} m' }});
    }
    
    selected.value = [];
}

setInterval(() => {
window.location.reload();
}, 60000);


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

.ma-5 {
    font-style: italic;

}

button
{
    display: flex;
    align-items: center;
    justify-content: center;
    margin: 0 auto;
    border: 2px solid #f5f5f5;
    color: black;
    font-size: 16px;
    cursor: pointer;
    border-radius: 12px; 
}

.mx-auto {
    display: block;
    color: rgb(255, 255, 255);
    background: linear-gradient(45deg, rgb(30, 161, 255), rgb(242, 234, 228));
    padding:"25px 50px 75px 100px;"
    
}

.ma-3 {
    display: block;
    padding-left: 150px;
    padding-right: 150px;
    

}

</style>
  