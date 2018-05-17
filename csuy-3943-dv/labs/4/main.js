const WIDTH = 800;
const HEIGHT = 400;

const drawBaseMap = (mapData, earthquakes, containerID) => {
	const maximumMagnitude = d3.max(mapData.features, d => d.properties.value);
	const minMagnitude = d3.mean(mapData.features, d => d.properties.value);
	const minMagnitude2 = d3.min(mapData.features, d => d.properties.value);
	const colorScale = d3.scaleLinear()
		.range(['#5e3c99', '#ffffbf' ,'#e66101'])
		.domain([minMagnitude2, minMagnitude, maximumMagnitude]);

	const container = d3.select(containerID);
	const projection = d3.geoNaturalEarth1()
		.fitSize([WIDTH, HEIGHT], mapData)
		.rotate([150, 0]);
	const path = d3.geoPath(projection);

	container.append('path')
		.datum({type: 'Sphere'})
		.attr('fill', 'white')
		.attr('stroke', 'black')
		.attr('stroke-width', 1)
		.attr('d', path);

	container.append('g')
		.selectAll('path')
		.data(mapData.features)
		.enter()
		.append('path')
		.attr('d', path)
		.attr('stroke', 'white')
		.attr('stroke-width', '0.5')
		.attr('fill', d => colorScale(d.properties.value));

	const graticule = d3.geoGraticule();
	container.append('g')
		.append('path')
		.datum(graticule)
		.attr('d', path)
		.attr('fill', 'none')
		.attr('stroke', 'gray')
		.attr('stroke-width', 0.5);

	plotEarthquakes(earthquakes, projection, container);
};

const plotEarthquakes = (earthquakes, projection, container) => {
	const positioned = earthquakes.map((d) => {
		const coords = projection([d.Longitude, d.Latitude]);
		[d.x, d.y] = coords;

		return d;
	});

	container.append('g')
		.selectAll('circle')
		.data(positioned)
		.enter()
		.append('circle')
		.attr('r', 3)
		.attr('cx', d => d.x)
		.attr('cy', d => d.y)
		.attr('opacity', 0.5)
		.attr('fill', 'green');
};

//This function merges the map geoinformation with the largest earthquake data, not that some contries don't have earthquake data, and it is fine.
const mergeInfoIntoMapData = (mapData, data) => {
	console.log(mapData.features.length - data.length);
	count = 0;
	mapData.features = mapData.features.map((geoFeature) => {
		let dataInfo = data.find(d => d.Country === geoFeature.properties.name);
		if (!dataInfo) {
			console.log('Didn\'t find', geoFeature.properties.name);
			return geoFeature;
		}

		geoFeature.properties.value = parseFloat(dataInfo.Magnitude);
		return geoFeature;
	});
};

const loadData = () => {
	return new Promise((resolve, reject) => {
		d3.queue()
			.defer(d3.json, 'countries.geo.json')
			.defer(d3.csv, 'largestEarthquakes.csv')
			.defer(d3.csv, 'earthquakes.csv')
			.await((err, ...data) => {
				if (err) {
					reject(err);
				} else {
					resolve(data);
				}
			});
	});
};

d3.select('#map')
	.attr('width', WIDTH)
	.attr('height', HEIGHT);

loadData().then(([mapData, largestEarthquakes, earthquakes]) => {
	mergeInfoIntoMapData(mapData, largestEarthquakes);
	drawBaseMap(mapData, earthquakes, '#map');
});
