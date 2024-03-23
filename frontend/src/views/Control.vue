<template>
    <div class="about">
      <div class="bg-light">
        <div class="container py-5">
          <div class="row h-100 align-items-center py-5">
            <div class="col-lg-6">
              <h1 class="display-4">
                Vue Fancy Weatherr
              </h1>
              <p class="lead text-muted mb-0">
                Vue Fancy Weather is a sleek and user-friendly weather app powered by Vue.js. It offers a stylish interface providing real-time weather updates, elegant date and time display, and insightful country information. Enjoy the simplicity of checking the weather with a touch of elegance.
              </p>
              <!-- <p class="lead text-muted">
                For documentation visit
                <a
                  href="https://vuejs.org/"
                  class="text-muted"
                >
                  <u>Vue</u>
                </a>
              </p> -->
            </div>
            <div class="col-lg-6 d-none d-lg-block">
              <img
                src="https://bootstrapious.com/i/snippets/sn-about/illus.png"
                alt=""
                class="img-fluid"
              >
            </div>
          </div>
        </div>
      </div>
  
      <div class="bg-white py-5">
        <div class="container py-5">
          <div class="row align-items-center mb-5">
            <div class="col-lg-6 order-2 order-lg-1">
              <h2 class="font-weight-light">
                Geocoding API
              </h2>
              <p class="font-italic text-muted mb-4">
                Geocoding API is a simple tool developed to ease the search for locations while working with geographic names and coordinates.
              </p>
              <a
                href="https://openweathermap.org/api/geocoding-api"
                class="btn btn-light px-5 rounded-pill shadow-sm"
              >
                Learn More
              </a>
            </div>
            <div class="col-lg-5 px-5 mx-auto order-1 order-lg-2">
              <img
                src="https://bootstrapious.com/i/snippets/sn-about/img-1.jpg"
                alt=""
                class="img-fluid mb-4 mb-lg-0"
              >
            </div>
          </div>
          <div class="row align-items-center">
            <div class="col-lg-5 px-5 mx-auto">
              <img
                src="https://bootstrapious.com/i/snippets/sn-about/img-2.jpg"
                alt=""
                class="img-fluid mb-4 mb-lg-0"
              >
            </div>
            <div class="col-lg-6">
              <h2 class="font-weight-light">
                REST Countries
              </h2>
              <p class="font-italic text-muted mb-4">
                This project is inspired by restcountries.eu by Fayder Florez. Although the original project has now moved to a subscription-based API, this project is still Open Source and Free to use.
              </p>
              <a
                href="https://restcountries.com/"
                class="btn btn-light px-5 rounded-pill shadow-sm"
              >
                Learn More
              </a>
            </div>
          </div>
        </div>
      </div>
    </div>
  </template>
  
  <script>
  
  export default {
    components: {
    },
    data() {
      return {
      }
    },
  }
  </script>
  
  <style scoped>
  </style>