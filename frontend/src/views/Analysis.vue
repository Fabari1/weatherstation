<template>
    <v-container class="bg-surface container" fluid>
      <v-row class="row">
        <v-col cols="3" align="center">
          <v-card
            title="Temperature"
            width="250"
            variant="outlined"
            color="primary"
            density="compact"
            rounded="lg"
          >
          <v-card-item class="mb-n5">
              <v-chip-group
                class="d-flex flex-row justify-center"
                color="primaryContainer"
                variant="flat"
              >
                <v-tooltip text="Min" location="start">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ temperature.min }}</v-chip>
                  </template>
                </v-tooltip>
  
                <v-tooltip text="Range" location="top">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ temperature.range }}</v-chip>
                  </template>
                </v-tooltip>
                <v-tooltip text="Max" location="end">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ temperature.max }}</v-chip>
                  </template>
                </v-tooltip>
              </v-chip-group>
            </v-card-item>
            <v-card-item align="center">
              <span class="text-h2 text-primary font-weight-bold">
                {{ temperature.avg }}
              </span>
            </v-card-item>
            <v-chip class="ma-2"> {{ isCelsius ? 'Celsius' : 'Fahrenheit' }} </v-chip> 
          </v-card>
        </v-col>
        <v-col cols="3" align="center">
          <v-card
            title="Humidity"
            width="250"
            variant="outlined"
            color="primary"
            density="compact"
            rounded="lg"
            >
            <v-card-item class="mb-n5">
              <v-chip-group
                class="d-flex flex-row justify-center"
                color="primaryContainer"
                variant="flat"
              >
                <v-tooltip text="Min" location="start">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ humidity.min }}</v-chip>
                  </template>
                </v-tooltip>
                
                <v-tooltip text="Range" location="top">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ humidity.range }}</v-chip>
                  </template>
                </v-tooltip>
                <v-tooltip text="Max" location="end">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ humidity.max }}</v-chip>
                  </template>
                </v-tooltip>
              </v-chip-group>
            </v-card-item>
            <v-card-item align="center">
              <span class="text-h2 text-primary font-weight-bold">
                {{ humidity.avg }}
              </span>
            </v-card-item>
            <v-chip class="ma-2"> Percent </v-chip>
          </v-card>
        </v-col>
        <v-col cols="3" align="center">
          <v-card
            title="Air Pressure"
            width="250"
            variant="outlined"
            color="primary"
            density="compact"
            rounded="lg"
            >
            <v-card-item class="mb-n5">
              <v-chip-group
                class="d-flex flex-row justify-center"
                color="primaryContainer"
                variant="flat"
                >
                <v-tooltip text="Min" location="start">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ pressure.min }}</v-chip>
                  </template>
                </v-tooltip>
                
                <v-tooltip text="Range" location="top">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ pressure.range }}</v-chip>
                  </template>
                </v-tooltip>
                <v-tooltip text="Max" location="end">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ pressure.max }}</v-chip>
                  </template>
                </v-tooltip>
              </v-chip-group>
            </v-card-item>
            <v-card-item align="center">
              <span class="text-h2 text-primary font-weight-bold">
                {{ pressure.avg }}
              </span>
            </v-card-item>
            <v-chip class="ma-2"> {{ isPressure ? 'Hectopascal' : 'Millimetre of Mercury' }} </v-chip>
          </v-card>
        </v-col>
        <v-col cols="3" align="center">
          <v-card
            title="Soil Moisture"
            width="250"
            variant="outlined"
            color="primary"
            density="compact"
            rounded="lg"
            >
            <v-card-item class="mb-n5">
              <v-chip-group
                class="d-flex flex-row justify-center"
                color="primaryContainer"
                variant="flat"
                >
                <v-tooltip text="Min" location="start">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ soilmoisture.min }}</v-chip>
                  </template>
                </v-tooltip>
                
                <v-tooltip text="Range" location="top">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ soilmoisture.range }}</v-chip>
                  </template>
                </v-tooltip>
                <v-tooltip text="Max" location="end">
                  <template v-slot:activator="{ props }">
                    <v-chip v-bind="props">{{ soilmoisture.max }}</v-chip>
                  </template>
                </v-tooltip>
              </v-chip-group>
            </v-card-item>
            <v-card-item align="center">
              <span class="text-h2 text-primary font-weight-bold">
                {{ soilmoisture.avg }}
              </span>
            </v-card-item>
            <v-chip class="ma-2"> Percent </v-chip>
          </v-card>
        </v-col>
      </v-row>
      <v-row class="ma-5">
        <v-col align="center" cols="12">
          <p>Enter date range for Analysis</p>
          <v-divider></v-divider>
          <br />
          <v-sheet class="sheet">
            <v-text-field
              v-model="start"
              label="Start date"
              type="Date"
              dense
              solo-inverted
              class="mr-5"
              :style="{ maxWidth: '210px' }"
              flat
            ></v-text-field>
            <v-text-field
              v-model="end"
              label="End date"
              type="Date"
              dense
              solo-inverted
              :style="{ maxWidth: '210px' }"
              flat
            ></v-text-field>
          </v-sheet>
            <br />
            <v-btn
              text="Analyze"
              class="mr-5"
              @click="
                updateLineCharts();
                updateCards(true);
                updateHistogramCharts();
                updateScatter();
              "
              color="primary"
              variant="tonal"
            ></v-btn>
          </v-col>
        </v-row>
         <v-row>
         <v-sheet class="w-25 ma-2">
            <v-form>
                <v-autocomplete
             
                clearable
                chips
                label="Convert Units"
                :items="[isCelsius ? 'Fahrenheit' : 'Celsius', isPressure ? 'Millimetre of Mercury' : 'Hectopascal']"
                multiple
                v-model="selected"
                variant="outlined"
                ></v-autocomplete>
              
            </v-form>
          </v-sheet>
          <v-btn   
            align="center" 
            class="ma-4"    
            color="primary"
            variant="tonal"
                @click="convertData()">
                Convert
            </v-btn>

          </v-row>
      <v-row class="row">
        <v-col cols="12">
          <figure class="highcharts-figure">
            <div id="container"></div>
          </figure>
        </v-col>
        <v-col cols="12">
          <figure class="highcharts-figure">
            <div id="container0"></div>
          </figure>
        </v-col>
      </v-row>
      <v-row class="row">
        <v-col class="col1" cols="12">
          <figure class="highcharts-figure">
            <div id="container1"></div>
          </figure>
        </v-col>
        <v-col cols="12">
          <figure class="highcharts-figure">
            <div id="container2"></div>
          </figure>
        </v-col>
        <v-col cols="12">
          <figure class="highcharts-figure">
            <div id="container4"></div>
          </figure>
        </v-col>
        <v-col cols="12">
          <figure class="highcharts-figure">
            <div id="container3"></div>
          </figure>
        </v-col>
      </v-row>
    </v-container>
  </template>
  
  <script setup>
  /** JAVASCRIPT HERE */
  
  import Highcharts from "highcharts";
  import more from "highcharts/highcharts-more";
  import Exporting from "highcharts/modules/exporting";
  import { withDirectives } from "vue";
  Exporting(Highcharts);
  more(Highcharts);
  
  // IMPORTS
  import { useMqttStore } from "@/store/mqttStore"; // Import Mqtt Store
  import { storeToRefs } from "pinia";
  
  import { useAppStore } from "@/store/appStore";
  import {
    ref,
    reactive,
    watch,
    onMounted,
    onBeforeUnmount,
    computed,
  } from "vue";
  import { useRoute, useRouter } from "vue-router";
  
  // VARIABLES
  const Mqtt = useMqttStore();
  const AppStore = useAppStore();
  const router = useRouter();
  const route = useRoute();
  var start = ref(null);
  var end = ref(null);
  var temperature = reactive({ min: 0, max: 0, avg: 0, range: 0 });
  var humidity = reactive({ min: 0, max: 0, avg: 0, range: 0 });
  var pressure = reactive({ min: 0, max: 0, avg: 0, range: 0 });
  var soilmoisture = reactive({ min: 0, max: 0, avg: 0, range: 0 });
  const tempHiLine = ref(null); // Chart object
  const humLine = ref(null); // Chart object
  const histo = ref(null); // Chart object
  const tempHiScat = ref(null); // Chart object
  const ampPresScat = ref(null); // Chart object
  const humScat = ref(null); // Chart object
  const isCelsius = ref(true);
  const isPressure = ref(true);
  const selected = ref([]);
  const rule = ref(true);
  // FUNCTIONS
  
  const CreateCharts = async () => {
    // TEMPERATURE CHART
    tempHiLine.value = Highcharts.chart("container", {
      chart: { zoomType: "x" },
      title: { text: "Air Temperature and Heat Index Analysis", align: "left" },
      subtitle: {
        text:
          " The heat index, also known as the apparent temperature, is a measure that combines air temperature and relative humidity to assess how hot it feels to the human body. " +
          "The relationship between heat index and air temperature is influenced by humidity levels. As humidity increases, the heat" +
          "index also rises, making the perceived temperature higher than the actual air temperature.",
      },
      yAxis: {
        title: {
          text: "Air Temperature & Heat Index",
          style: { color: "#000000" },
        },
        labels: { format: "{value} °C" },
      },
  
      tooltip: {
        pointFormat: "Heatindex: {point.x} °C <br/> Temperature: {point.y} °C",
      },
      xAxis: {
        type: "datetime",
        title: { text: "Time", style: { color: "#000000" } },
      },
      tooltip: { shared: true },
      series: [
        {
          name: "Temperature",
          type: "line",
          data: [],
          turboThreshold: 0,
          color: Highcharts.getOptions().colors[0],
        },
        {
          name: "Heat Index",
          type: "line",
          data: [],
          turboThreshold: 0,
          color: Highcharts.getOptions().colors[1],
        },
      ],
    });
  
    humLine.value = Highcharts.chart("container0", {
      chart: { zoomType: "x" },
      title: { text: "Humidity Analysis", align: "left" },
      yAxis: {
        title: {
          text: "Humidity",
          style: { color: "#000000" },
        },
        labels: { format: "{value} %" },
      },
  
      tooltip: {
        pointFormat: "Humidity: {point.x} % ",
      },
      xAxis: {
        type: "datetime",
        title: { text: "Time", style: { color: "#000000" } },
      },
      tooltip: { shared: true },
      series: [
        {
          name: "Humidity",
          type: "line",
          data: [],
          turboThreshold: 0,
          color: Highcharts.getOptions().colors[0],
        },
      ],
    });
  
    histo.value = Highcharts.chart("container1", {
      chart: { zoomType: "x" },
      title: { text: "Frequency Distribution Analysis", align: "left" },
      yAxis: {
        title: {
          text: "Frequency",
          style: { color: "#000000" },
        },
        labels: { format: "{value}" },
      },
  
      xAxis: {
        title: { text: "Value %/°C ", style: { color: "#000000" } },
      },
      tooltip: { shared: true },
      series: [
        {
          name: "Temperature",
          type: "bar",
          data: [],
          turboThreshold: 0,
          color: Highcharts.getOptions().colors[0],
        },
        {
          name: "Humidity",
          type: "bar",
          data: [],
          turboThreshold: 0,
          color: Highcharts.getOptions().colors[1],
        },
        {
          name: "Heat Index",
          type: "bar",
          data: [],
          turboThreshold: 0,
          color: Highcharts.getOptions().colors[3],
        },
      ],
    });
  
    tempHiScat.value = Highcharts.chart("container2", {
      chart: { zoomType: "x" },
      title: {
        text: "Temperature & Heat Index Correlation Analysis",
        align: "left",
      },
      subtitle: {
        text: "Visualize the relationship between Temperature and Heat Index as well as revealing patterns or trends in the data",
      },
      yAxis: {
        title: {
          text: "Heat Index",
          style: { color: "#000000" },
        },
        labels: { format: "{value} °C" },
      },
  
      xAxis: {
        title: { text: "Temperature", style: { color: "#000000" } },
        labels: { format: "{value} °C" },
      },
      tooltip: {
        shared: true,
        pointFormat: "Temperature: {point.x} °C <br/> Heat Index: {point.y} °C",
      },
      series: [
        {
          name: "Analysis",
          type: "scatter",
          data: [],
          turboThreshold: 0,
          color: Highcharts.getOptions().colors[0],
        },
      ],
    });

    ampPresScat.value = Highcharts.chart("container4", {
      chart: { zoomType: "x" },
      title: {
        text: "Altitude & Pressure Correlation Analysis",
        align: "left",
      },
      subtitle: {
        text: "Visualize the relationship between Altitude and Pressure as well as revealing patterns or trends in the data",
      },
      yAxis: {
        title: {
          text: "Altitude",
          style: { color: "#000000" },
        },
        labels: { format: "{value} m" },
      },
  
      xAxis: {
        title: { text: "Pressure", style: { color: "#000000" } },
        labels: { format: "{value} hPa" },
      },
      tooltip: {
        shared: true,
        pointFormat: "Pressure: {point.x} hPa <br/> Altitude: {point.y} m",
      },
      series: [
        {
          name: "Analysis",
          type: "scatter",
          data: [],
          turboThreshold: 0,
          color: Highcharts.getOptions().colors[0],
        },
      ],
    });
  
    humScat.value = Highcharts.chart("container3", {
      chart: { zoomType: "x" },
      title: {
        text: "Humidity & Heat Index Correlation Analysis",
        align: "left",
      },
      subtitle: {
        text: "Visualize the relationship between Humidity and Heat Index as well as revealing patterns or trends in the data",
      },
      yAxis: {
        title: {
          text: "Heat Index",
          style: { color: "#000000" },
        },
        labels: { format: "{value} °C" },
      },
  
      xAxis: {
        title: { text: "Humidity", style: { color: "#000000" } },
        labels: { format: "{value} %" },
      },
      tooltip: {
        shared: true,
        pointFormat: "Humidity: {point.x} °C <br/> Heat Index: {point.y} °C",
      },
      series: [
        {
          name: "Analysis",
          type: "scatter",
          data: [],
          turboThreshold: 0,
          color: Highcharts.getOptions().colors[5],
        },
      ],
    });
  };
  
  onMounted(() => {
    // THIS FUNCTION IS CALLED AFTER THIS COMPONENT HAS BEEN MOUNTED
    Mqtt.connect(); // Connect to Broker located on the backend
    setTimeout(() => {
      // Subscribe to each topic
      Mqtt.subscribe("620154701");
      Mqtt.subscribe("620154701_sub");
    }, 3000);
    CreateCharts();
  });
  
  onBeforeUnmount(() => {
    // THIS FUNCTION IS CALLED RIGHT BEFORE THIS COMPONENT IS UNMOUNTED
    Mqtt.unsubcribeAll();
  });
  
  const updateLineCharts = async () => {
    if (!!start.value && !!end.value) {
      // Convert output from Textfield components to 10 digit timestamps
      let startDate = new Date(start.value).getTime() / 1000;
      let endDate = new Date(end.value).getTime() / 1000;
      // Fetch data from backend
      const data = await AppStore.getAllInRange(startDate, endDate);
      // Create arrays for each plot
      let temperature = [];
      let heatindex = [];
      let humidity = [];
     
   
      // Iterate through data variable and transform object to format recognized by highcharts
    if(selected.value.includes("Celsius") || selected.value.length==0){
      data.forEach((row) => {
        temperature.push({
          x: row.timestamp * 1000,
          y: parseFloat(row.temperature.toFixed(2)),
        });
        heatindex.push({
          x: row.timestamp * 1000,
          y: parseFloat(row.heatindex.toFixed(2)),
        });
        humidity.push({
          x: row.timestamp * 1000,
          y: parseFloat(row.humidity.toFixed(2)),
        });
      });
    }else if(selected.value.includes("Fahrenheit") ||  selected.value.length>=0){
      data.forEach((row) => {
        temperature.push({
          x: row.timestamp * 1000,
          y: parseFloat(celsiusToFahrenheit(row.temperature).toFixed(2)),
        });
        heatindex.push({
          x: row.timestamp * 1000,
          y: parseFloat(celsiusToFahrenheit(row.heatindex).toFixed(2)),
        });
        humidity.push({
          x: row.timestamp * 1000,
          y: parseFloat(row.humidity.toFixed(2)),
        });
      });
    }
    // Add data to Temperature and Heat Index chart
    tempHiLine.value.series[0].setData(temperature);
    tempHiLine.value.series[1].setData(heatindex);
    humLine.value.series[0].setData(humidity);
    
      };
    };
  
  const updateCards = async (rule) => {
    // Retrieve Min, Max, Avg, Spread/Range
    if (!!start.value && !!end.value && rule) {

      // 1. Convert start and end dates collected fron TextFields to 10 digit timestamps
      let startDate = new Date(start.value).getTime() / 1000;
      let endDate = new Date(end.value).getTime() / 1000;
      // 2. Fetch data from backend by calling the API functions
      const temp = await AppStore.getTemperatureMMAR(startDate, endDate);
      const humid = await AppStore.getHumidityMMAR(startDate, endDate);
      const air = await AppStore.getPressureMMAR(startDate, endDate);
      const soil= await AppStore.getSoilMMAR(startDate, endDate);
   

      temperature.max = temp[0].max.toFixed(1);
      temperature.min = temp[0].min.toFixed(1);
      temperature.avg = temp[0].avg.toFixed(1);
      temperature.range = temp[0].range.toFixed(1);

      humidity.max = humid[0].max.toFixed(1);
      humidity.min = humid[0].min.toFixed(1);
      humidity.avg = humid[0].avg.toFixed(1);
      humidity.range = humid[0].range.toFixed(1);

      pressure.min = air[0].min.toFixed(1);
      pressure.max = air[0].max.toFixed(1);
      pressure.avg = air[0].avg.toFixed(1);
      pressure.range = air[0].range.toFixed(1);

      soilmoisture.min = soil[0].min.toFixed(1);
      soilmoisture.max = soil[0].max.toFixed(1);
      soilmoisture.avg = soil[0].avg.toFixed(1);
      soilmoisture.range = soil[0].range.toFixed(1);
    };
    if(selected.value.includes("Fahrenheit")){
      temperature.max = celsiusToFahrenheit(temperature.max).toFixed(1);
      temperature.min = celsiusToFahrenheit(temperature.min).toFixed(1);
      temperature.avg = celsiusToFahrenheit(temperature.avg).toFixed(1);
      temperature.range = (temperature.max - temperature.min).toFixed(1);

    }
    if(selected.value.includes("Celsius")){
      temperature.max = fahrenheitToCelsius(temperature.max).toFixed(1);
      temperature.min = fahrenheitToCelsius(temperature.min).toFixed(1);
      temperature.avg = fahrenheitToCelsius(temperature.avg).toFixed(1);
      temperature.range = (temperature.max - temperature.min).toFixed(1);
    }

    if(selected.value.includes("Millimetre of Mercury")){
      pressure.min = hPascalToMmHg(pressure.min).toFixed(1);
      pressure.max = hPascalToMmHg(pressure.max).toFixed(1);
      pressure.avg = hPascalToMmHg(pressure.avg).toFixed(1);
      pressure.range = (pressure.max - pressure.min).toFixed(1);
    }

    if(selected.value.includes("Hectopascal")){
      pressure.min = mmHgToHPascal(pressure.min).toFixed(1);
      pressure.max = mmHgToHPascal(pressure.max).toFixed(1);
      pressure.avg = mmHgToHPascal(pressure.avg).toFixed(1);
      pressure.range = (pressure.max - pressure.min).toFixed(1);
    }

    

  };
  
  const updateHistogramCharts = async () => {
    // Retrieve Min, Max, Avg, Spread/Range for Column graph
    let startDate = new Date(start.value).getTime() / 1000;
    let endDate = new Date(end.value).getTime() / 1000;
    if (!!start.value && !!end.value) {
      const temp = await AppStore.getFreqDistro( "temperature", startDate, endDate );
      const humid = await AppStore.getFreqDistro("humidity", startDate, endDate);
      const hi = await AppStore.getFreqDistro("heatindex", startDate, endDate);
      // 3. create an empty array for each variable (temperature, humidity and heatindex)
      // see example below
    
      let temperature = [];
      let humidity = [];
      let heatindex = [];
      temp.forEach((row) => {
        temperature.push({ x: row["_id"], y: row["count"] });
      });
      humid.forEach((row) => {
        humidity.push({ x: row["_id"], y: row["count"] });
      });
      hi.forEach((row) => {
        heatindex.push({ x: row["_id"], y: row["count"] });
      });
      
      histo.value.series[0].setData(temperature);
      histo.value.series[1].setData(humidity);
      histo.value.series[2].setData(heatindex);
    }
  };
  
  
  const updateScatter = async () => {
    if (!!start.value && !!end.value) {
      let startDate = new Date(start.value).getTime() / 1000;
      let endDate = new Date(end.value).getTime() / 1000;
      // Convert output from Textfield components to 10 digit timestamps
      // Fetch data from backend
      const data = await AppStore.getAllInRange(startDate, endDate);
      console.log(data);
      // Create arrays for each plot
      let scatterPoints1 = [];
      let scatterPoints2 = [];
      let scatterPoints3 = [];
     
      // Iterate through data variable and transform object to format recognized by highcharts
    if(selected.value.includes("Celsius") || selected.value.includes("Hectopascal") ||  selected.value.length==0){
      
     data.forEach((row) => {
        scatterPoints1.push({
          x: parseFloat(row.temperature.toFixed(2)),
          y: parseFloat(row.heatindex.toFixed(2)),
        });
        scatterPoints2.push({
          x: parseFloat(row.humidity.toFixed(2)),
          y: parseFloat(row.heatindex.toFixed(2)),
        });
        scatterPoints3.push({
          x: parseFloat(row.pressure.toFixed(2)),
          y: parseFloat(row.altitude.toFixed(2)),
        });
      });}
      if(selected.value.includes("Fahrenheit")){
        scatterPoints1 = [];
        scatterPoints2 = [];
       
        data.forEach((row) => {
          scatterPoints1.push({
            x: parseFloat(celsiusToFahrenheit(row.temperature).toFixed(2)),
            y: parseFloat(celsiusToFahrenheit(row.heatindex).toFixed(2)),
          });
          scatterPoints2.push({
            x: parseFloat(row.humidity.toFixed(2)),
            y: parseFloat(celsiusToFahrenheit(row.heatindex).toFixed(2)),
          });
         
        });
      }

      if (selected.value.includes("Millimetre of Mercury")){
     
        scatterPoints3 = [];
        data.forEach((row) => {
        scatterPoints3.push({
          x: parseFloat(hPascalToMmHg(row.pressure).toFixed(2)),
          y: parseFloat(row.altitude.toFixed(2)),
        });
      });  }

      /*
      if(selected.value.includes("Celsius") || selected.value==[]){
       if (selected.value.includes("Fahrenheit")){
      data.forEach((row) => {
        scatterPoints1.push({
          x: parseFloat(celsiusToFahrenheit(row.temperature).toFixed(2)),
          y: parseFloat(celsiusToFahrenheit(row.heatindex).toFixed(2)),
        });
      });
      
      data.forEach((row) => {
        scatterPoints2.push({
          x: parseFloat(row.humidity.toFixed(2)),
          y: parseFloat(celsiusToFahrenheit(row.heatindex).toFixed(2)),
        });
      });}
      else 
        data.forEach((row) => {
        scatterPoints1.push({
          x: parseFloat(row.temperature.toFixed(2)),
          y: parseFloat(row.heatindex.toFixed(2)),
        });
      });}

      if (selected.value.includes("Hectopascal") || selected.value==[]){
        data.forEach((row) => {
        scatterPoints3.push({
          x: parseFloat(row.pressure.toFixed(2)),
          y: parseFloat(row.altitude.toFixed(2)),
        });
      });
      }
    //   if (selected.value.includes("Millimetre of Mercury")){
    //     data.forEach((row) => {
    //     scatterPoints3.push({
    //       x: parseFloat(hPascalToMmHg(row.pressure).toFixed(2)),
    //       y: parseFloat(row.altitude.toFixed(2)),
    //     });
    //   });  
    // }
      */
      // Add data to Temperature and Heat Index chart
      tempHiScat.value.series[0].setData(scatterPoints1);
      humScat.value.series[0].setData(scatterPoints2);
      ampPresScat.value.series[0].setData(scatterPoints3);
    }
  };

  const celsiusToFahrenheit = (celsius) => {
        return (celsius * (9 / 5)) + 32;
      };

  const fahrenheitToCelsius = (fahrenheit) => {
        return (fahrenheit - 32) * (5 / 9);
      };

  const hPascalToMmHg = (hPascal) => {
        return hPascal * 0.750061561303;
      };

  const mmHgToHPascal = (mmHg) => {
        return mmHg / 0.750061561303;
      };

  const convertData = async () => {
  if(selected.value.includes("Fahrenheit")){
    isCelsius.value = false;
    histo.value.xAxis[0].update({title: { text: "Value %/°F" , style:{color:'#000000'}}});
    tempHiLine.value.yAxis[0].update({title: { text: '°F' , style:{color:'#000000'}}});
    tempHiLine.value.yAxis[0].update({labels: { format:'{value} °F' }});
    tempHiScat.value.yAxis[0].update({title: { text: '°F' , style:{color:'#000000'}}});
    tempHiScat.value.yAxis[0].update({labels: { format:'{value} °F' }});
    humScat.value.yAxis[0].update({labels: { format: '{value} °F' }});
  };

  if(selected.value.includes("Celsius")){
    isCelsius.value = true;
    histo.value.xAxis[0].update({title: { text: "Value %/°C" , style:{color:'#000000'}}});
    tempHiLine.value.yAxis[0].update({title: { text: '°C' , style:{color:'#000000'}}});
    tempHiLine.value.yAxis[0].update({labels: { format:'{value} °C' }});
    tempHiScat.value.yAxis[0].update({title: { text: '°C' , style:{color:'#000000'}}});
    tempHiScat.value.yAxis[0].update({labels: { format:'{value} °C' }});
    humScat.value.yAxis[0].update({labels: { format: '{value} °C' }});
  }

  if(selected.value.includes("Millimetre of Mercury")){
    isPressure.value = false;
    ampPresScat.value.xAxis[0].update({title: { text: 'Pressure (mmHg)' , style:{color:'#000000'}}});
    ampPresScat.value.xAxis[0].update({labels: { format:'{value} mmHg' }});
  };

  if(selected.value.includes("Hectopascal")){
    isPressure.value = true;
    ampPresScat.value.xAxis[0].update({title: { text: 'Pressure (hPa)' , style:{color:'#000000'}}});
    ampPresScat.value.xAxis[0].update({labels: { format:'{value} hPa' }});
  };
  
    updateLineCharts();
    updateCards(false);
    updateHistogramCharts();
    updateScatter();

    setTimeout(() => {
      selected.value = [];
    }, 10000);

  };

  
  </script>
  
  <style scoped>
  /** CSS STYLE HERE */
  
  .container {
    /* background-color: #f5f5f5; */
   
    width: 1200px;
  }
  
  .row {
    max-width: 1200px;
  }
  
  .ma-5 {
    display: flex;
    align-items: center;
    justify-content: center;
    margin: 0 auto;

  }
  
  .col1 {
    border: black;
  }
  
  .sheet {
    display: flex;
    align-items: center;
    justify-content: center;
    height: 100px;
    width: 100%;
  }
  
  Figure {
    border: 2px solid black;
  }
  </style>