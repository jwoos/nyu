const DIMENSION = {
	width: 1200,
	height: 600,
	margin: {
		x: 50,
		y: 50
	},
	radius: 60
};
const CONTAINER = {
	a: '#a',
	b: '#b',
	c: '#c'
};

const loadData = () => {
	return new Promise((resolve, reject) => {
		d3.queue()
			.defer(d3.json, 'countries.geo.json')
			.defer(d3.csv, 'donation.csv')
			.defer(d3.csv, 'donation_by_year.csv')
			.defer(d3.csv, 'purpose.csv')
			.await((err, ...data) => {
				if (err) {
					reject(err);
				} else {
					resolve(data);
				}
			});
	});
};

const mergeData = (mapData, donation, donationByYear, donationPurpose) => {
	const donationMap = {};
	donation.forEach((elem) => {
		donationMap[elem.country] = {
			donated: parseFloat(elem.donated) || 0,
			received: parseFloat(elem.received) || 0
		};

		const country = donationMap[elem.country];
		country.ratio = country.received / (country.received + country.donated);
	});

	donationByYear.forEach((elem) => {
		const country = donationMap[elem.country];

		if (!country.years) {
			country.years = {};
		}

		country.years[parseInt(elem.year)] = {
			donated: parseFloat(elem.donated) || 0,
			received: parseFloat(elem.received) || 0
		};
	});

	donationPurpose.forEach((elem) => {
		const country = donationMap[elem.country];

		if (!country.purposes) {
			country.purposes = {};
		}

		country.purposes[elem.purpose] = {
			donated: parseFloat(elem.donated) || 0,
			received: parseFloat(elem.received) || 0
		};
	});

	mapData.features = mapData.features.map((feature) => {
		feature.properties.donation = donationMap[feature.properties.name] || {};
		return feature;
	});
};

const init = (container) => {
	for (let k of Object.keys(container)) {
		d3.select(CONTAINER[k])
			.attr('width', DIMENSION.width)
			.attr('height', DIMENSION.height);
	}
};

const graphA = (mapData) => {
	const min = 0;
	const mid = 0.5;
	const max = 1;
	const colorScale = d3.scaleLinear()
		.range(['red', 'white', 'green'])
		.domain([min, mid, max]);

	const container = d3.select(CONTAINER.a);
	const projection = d3.geoEquirectangular()
		.fitSize([DIMENSION.width, DIMENSION.height], mapData);
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
		.attr('fill', d => colorScale(d.properties.donation.ratio))
		.append('title')
		.text(d => `Name: ${d.properties.name}\nReceived: ${d.properties.donation.received}\nDonated: ${d.properties.donation.donated}\nRatio: ${d.properties.donation.ratio}`);

	const graticule = d3.geoGraticule();
	container.append('g')
		.append('path')
		.datum(graticule)
		.attr('d', path)
		.attr('fill', 'none')
		.attr('stroke', 'gray')
		.attr('stroke-width', 0.5);
};

const graphB = (data) => {
	data = data.map((d) => {
		d.received = parseFloat(d.received) || 0;
		d.donated = parseFloat(d.donated) || 0;
		d.year = parseInt(d.year);
		d.ratio = (d.received / (d.received  + d.donated)) * 100;
		return d;
	});

	const yearRange = d3.extent(data, d => d.year);
	const max = d3.max(data, d => d.ratio);

	const xScale = d3.scaleLinear()
		.range([0, DIMENSION.width - (DIMENSION.margin.x * 2)])
		.domain(yearRange);

	const yScale = d3.scaleLinear()
		.range([0, DIMENSION.height - (DIMENSION.margin.y * 2)])
		.domain([max, 0]);

	const colorScale = d3.scaleOrdinal()
		.range([...d3.schemeCategory10, ...d3.schemeCategory20, ...d3.schemeCategory20b, ...d3.schemeCategory20c])
		.domain(data.map(d => d.country));

	const map = {};
	data.forEach((e) => {
		if (!map[e.country]) {
			map[e.country] = []
		}

		map[e.country].push(e);
	});

	const container = d3.select(CONTAINER.b)
		.append('g')
		.attr('transform', `translate(${DIMENSION.margin.x}, ${DIMENSION.margin.y})`);

	for (let country of Object.keys(map)) {
		const countryData = map[country];
		const line = d3.line()
			.x(d => xScale(d.year))
			.y(d => yScale(d.ratio));

		container.append('path')
			.datum(countryData.sort((a, b) => {
				if (a.year < b.year) {
					return -1
				} else if (a.year > b.year) {
					return 1;
				}

				return 0;
			}))
			.attr('fill', 'none')
			.attr('stroke', colorScale(country))
			.attr('d', line)
			.append('title')
			.text(d => `Country: ${d[0].country}`);
	}

	const yAxis = d3.axisLeft(yScale);
	const xAxis = d3.axisBottom(xScale);

	d3.select(CONTAINER.b)
		.append('g')
		.attr('transform', `translate(${DIMENSION.margin.x}, ${DIMENSION.margin.y})`)
		.call(yAxis)
		.append('text')
		.text('% of Received')
		.attr('dx', -(DIMENSION.height - DIMENSION.margin.x * 2) / 2)
		.attr('dy', -DIMENSION.margin.x / 2)
		.attr('text-anchor', 'middle')
		.attr('fill', 'black')
		.attr('transform', 'rotate(270)');

	d3.select(CONTAINER.b)
		.append('g')
		.attr('transform', `translate(${DIMENSION.margin.x}, ${DIMENSION.height - DIMENSION.margin.y})`)
		.call(xAxis)
		.append('text')
		.text('Year')
		.attr('dx', (DIMENSION.width - DIMENSION.margin.x * 2) / 2)
		.attr('dy', DIMENSION.margin.y / 2 )
		.attr('text-anchor', 'middle')
		.attr('fill', 'black');
};

const graphC = (mapData, donationPurpose) => {
	const container = d3.select(CONTAINER.c);
	const projection = d3.geoEquirectangular()
		.fitSize([DIMENSION.width, DIMENSION.height], mapData);
	const path = d3.geoPath(projection);

	let purposes = [];
	mapData.features.forEach((e) => {
		if (e.properties.donation.purposes) {
			purposes = [...purposes, ...Object.keys(e.properties.donation.purposes)];
		}
	});
	const colorScale = d3.scaleOrdinal()
		.range([...d3.schemeCategory10, ...d3.schemeCategory20, ...d3.schemeCategory20b, ...d3.schemeCategory20c])
		.domain(purposes);

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
		.append('title')
		.text(d => `Name: ${d.properties.name}`);

	const graticule = d3.geoGraticule();
	container.append('g')
		.append('path')
		.datum(graticule)
		.attr('d', path)
		.attr('fill', 'none')
		.attr('stroke', 'gray')
		.attr('stroke-width', 0.5);

	const map = {};
	donationPurpose.forEach((e) => {
		if (!map[e.country]) {
			map[e.country] = [];
		}

		const coords = projection([e.longitude, e.latitude]);
		[e.x, e.y] = coords;

		e.received = parseFloat(e.received) || 0;
		e.donated = parseFloat(e.donated) || 0;

		map[e.country].push(e);
	});

	for (let country of Object.keys(map)) {
		const countryData = map[country];
		const pie = d3.pie()
			.sort(null)
			.value((d) => d.received);

		const path = d3.arc()
			.outerRadius(DIMENSION.radius - DIMENSION.margin.x)
			.innerRadius(0);

		const label = d3.arc()
			.outerRadius(DIMENSION.radius - DIMENSION.margin.x)
			.innerRadius(DIMENSION.radius - DIMENSION.margin.x);

		const arc = container.append('g')
			.data(countryData)
			.attr('transform', d => `translate(${d.x}, ${d.y})`)
			.selectAll('.arc')
			.data(pie(countryData))
			.enter()
			.append('g')
			.attr('class', 'arc');

		arc.append('path')
			.attr('d', path)
			.attr('fill', d => colorScale(d.data.purpose));

		arc.append('title')
			.text(d => `Name: ${d.data.country}\nReceived: ${d.data.received}\nPurpose: ${d.data.purpose}`);

		//container.
			//.selectAll('path')
			//.data(countryData)
			//.append('path')
	}

};

loadData().then(([mapData, donation, donationByYear, donationPurpose]) => {
	// initialize
	init(CONTAINER);

	// merge into features
	mergeData(mapData, donation, donationByYear, donationPurpose);

	graphA(mapData);
	graphB(donationByYear);
	graphC(mapData, donationPurpose);
});
