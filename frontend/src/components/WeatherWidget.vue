<template>
  <div class="wrapper mt-4">
    <div class="main-container">
      <div class="info-side">
        <!-- <div class="today-info-container">
          <div class="today-info">
            <div class="precipitation"> <span class="title">PRECIPITATION</span><span class="value">0 %</span>
              <div class="clear" />
            </div>
            <div class="humidity"> <span class="title">HUMIDITY</span><span class="value">34 %</span>
              <div class="clear" />
            </div>
            <div class="wind"> <span class="title">WIND</span><span class="value">0 km/h</span>
              <div class="clear" />
            </div>
          </div>
        </div> -->
        <!-- <div class="week-container">
          <ul class="week-list">
            <li class="active">
              <i
                class="day-icon"
                data-feather="sun"
              /><span class="day-name">Tue</span><span class="day-temp">29°C</span>
            </li>
            <li><i
              class="day-icon"
              data-feather="cloud"
            /><span class="day-name">Wed</span><span class="day-temp">21°C</span></li>
            <li><i
              class="day-icon"
              data-feather="cloud-snow"
            /><span class="day-name">Thu</span><span class="day-temp">08°C</span></li>
            <li><i
              class="day-icon"
              data-feather="cloud-rain"
            /><span class="day-name">Fry</span><span class="day-temp">19°C</span></li>
            <div class="clear" />
          </ul>
        </div> -->
        <!-- <div class="location-container">
          <button class="location-button">
            <i data-feather="map-pin" /><span>Change location</span>
          </button>
        </div> -->

        <div class="info-title">
          <h5>CURRENT WEATHER</h5>
        </div>

        <div>
          <div class="info-item">
            <div class="info-label">
              {{ city }}, {{ countryCode }}
            </div>
            <div class="info-value">
              Today {{ currentDayName }} {{ time }}
            </div>
          </div>
          <div class="info-item">
            <div class="info-label">
              {{ temperature }}<span>°C</span>
            </div>
            <div class="info-value">
              {{ weather.weather[0].main }}
            </div>
          </div>
          <div class="info-item">
            <img
              :src="`http://openweathermap.org/img/w/${weather.weather[0].icon}.png`"
              alt="weather icon"
              class="weather-icon"
            >
          </div>
        </div>

        <div class="info-title">
          <h5>AIR CONDITIONS</h5>
        </div>

        <div class="info-items">
          <div class="info-item">
            <div class="info-label">
              <font-awesome-icon icon="fa-solid fa-temperature-half" />
              Feels Like
            </div>
            <div class="info-value">
              {{ feelsLike }}°C
            </div>
          </div>
          <div class="info-item">
            <div class="info-label">
              <font-awesome-icon icon="fa-solid fa-wind" />
              Wind
            </div>
            <div class="info-value">
              {{ weather.wind.speed }} m/s
            </div>
          </div>
          <div class="info-item">
            <div class="info-label">
              <font-awesome-icon icon="fa-solid fa-cloud" />
              Clouds
            </div>
            <div class="info-value">
              {{ weather.clouds.all }}%
            </div>
          </div>
          <div class="info-item">
            <div class="info-label">
              <font-awesome-icon icon="fa-solid fa-droplet" />
              Humidity
            </div>
            <div class="info-value">
              {{ weather.main.humidity }}%
            </div>
          </div>
        </div>
      </div>

      <div class="weather-side float-right">
        <div class="weather-gradient" />
        <div class="date-container">
          <h2 class="date-dayname">
            {{ currentDayName }}
          </h2>
          <span class="date-day">{{ fullLocalDate }}</span>
          <span class="location">{{ city }}, {{ countryCode }}</span>
        </div>
        <div class="weather-container">
          <img
            :src="`http://openweathermap.org/img/w/${weather.weather[0].icon}.png`"
            alt="weather icon"
            class="weather-icon"
          >
          <h1 class="weather-temp">
            {{ temperature }}<span>°C</span>
          </h1>
          <h3 class="weather-desc">
            {{ weather.weather[0].main }}
          </h3>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
const moment = require('moment')

export default {
  name: 'WeatherWidget',
  props: {
    city: {
      type: String,
      default: '',
    },
    countryCode: {
      type: String,
      default: '',
    },
    dateTime: {
      type: String,
      default: '',
    },
    weather: {
      type: Object,
      default: () => ({}),
    },
  },
  data() {
    return {
    }
  },
  computed: {
    date() {
      return this.dateTime.split(' ')[0]
    },
    time() {
      const time24Hours = this.dateTime.split(' ')[1]
      const timeAmPm = moment(time24Hours, 'HH:mm').format('h:mm A')
      return timeAmPm
    },
    currentDayName() {
      return moment(this.date).format('dddd')
    },
    currentMonthShort() {
      const month = moment(this.date).month()
      return moment.monthsShort()[month]
    },
    fullLocalDate() {
      const date = this.date.split('-')
      return `${date[2]} ${this.currentMonthShort} ${date[0]}`
    },
    temperature() {
      if (this.weather && this.weather.main && this.weather.main.temp) {
        // Convert Kelvin to Celsius
        const temperatureInCelsius = this.weather.main.temp - 273.15
        return temperatureInCelsius.toFixed(0)
      }
      return ''
    },
    feelsLike() {
      if (this.weather && this.weather.main && this.weather.main.feels_like) {
        // Convert Kelvin to Celsius
        const temperatureInCelsius = this.weather.main.feels_like - 273.15
        return temperatureInCelsius.toFixed(0)
      }
      return ''
    },
  },
  methods: {
  },
}
</script>

<style scoped>
@import '~@/assets/scss/weather-widget.scss';
</style>
