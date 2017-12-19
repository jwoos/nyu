const DIMENSION = {
	width: 1900,
	height: 900,
	margin: {
		x: 100,
		y: 100,
		top: 175,
		left: 175,
		right: 10,
		bottom: 10
	},
	offset: 10
};

const DIGITS = 2;

const CONTAINER = '#chart';

const loadData = () => {
	return new Promise((resolve, reject) => {
		d3.queue()
			.defer(d3.csv, 'donations_donnor_recipient_amount_geo.csv')
			.await((err, ...data) => {
				if (err) {
					reject(err);
				} else {
					resolve(data);
				}
			});
	});
};

const init = (container) => {
	d3.select(CONTAINER)
		.attr('width', DIMENSION.width)
		.attr('height', DIMENSION.height);
};

const transformData = (data) => {
	const transformed = {
		uniqueDonor: {},
		uniqueDonorArray: [],
		uniqueRecipient: {},
		uniqueRecipientArray: []
	};

	for (let val of data) {
		const recipient = val.recipient;
		const donor = val.donor;

		if (!transformed.uniqueDonor[donor]) {
			transformed.uniqueDonor[donor] = {
				count: 1,
				amount: parseFloat(val.amount)
			};
		} else {
			transformed.uniqueDonor[donor].count++;
			transformed.uniqueDonor[donor].amount += parseFloat(val.amount);
		}

		if (!transformed.uniqueRecipient[recipient]) {
			transformed.uniqueRecipient[recipient] = {
				count: 1,
				amount: parseFloat(val.amount)
			};
		} else {
			transformed.uniqueRecipient[recipient].count++;
			transformed.uniqueRecipient[recipient].amount += parseFloat(val.amount);
		}
	}

	for (let key of Object.keys(transformed.uniqueDonor)) {
		transformed.uniqueDonorArray.push({
			...transformed.uniqueDonor[key],
			name: key
		});
	}

	for (let key of Object.keys(transformed.uniqueRecipient)) {
		transformed.uniqueRecipientArray.push({
			...transformed.uniqueRecipient[key],
			name: key
		});
	}

	const compareFn = (a, b) => {
		const comp = b.count - a.count;

		if (comp !== 0) {
			return comp;
		} else {
			return b.amount - a.amount;
		}
	};

	transformed.uniqueDonorArray.sort(compareFn);
	transformed.uniqueRecipientArray.sort(compareFn);

	return transformed;
};

loadData().then(([data]) => {
	init(CONTAINER);

	const transformedData = transformData(data);

	const min = d3.min(data, d => d.amount);
	const max = d3.max(data, d => d.amount);

	const container = d3.select(CONTAINER);
	const colorScale = d3.scaleLinear()
		.range(['AntiqueWhite', 'blue'])
		.domain([min, max]);

	const uniqueRecipient = transformedData.uniqueRecipient;
	const uniqueRecipientArray = transformedData.uniqueRecipientArray;
	const uniqueDonor = transformedData.uniqueDonor;
	const uniqueDonorArray = transformedData.uniqueDonorArray;

	const xScale = d3.scaleBand()
		.range([0, DIMENSION.width - (DIMENSION.margin.left + DIMENSION.margin.right)])
		.domain(uniqueRecipientArray.map(d => d.name));

	const yScale = d3.scaleBand()
		.range([0, DIMENSION.height - (DIMENSION.margin.top + DIMENSION.margin.bottom)])
		.domain(uniqueDonorArray.map(d => d.name));

	container.append('g')
		.attr('transform', `translate(${DIMENSION.margin.left - DIMENSION.offset}, ${DIMENSION.margin.top - DIMENSION.offset})`)
		.selectAll('text')
		.data(uniqueDonorArray)
		.enter()
		.append('text')
		.text(d => `${d.name} | ${d.count} | $${d.amount.toExponential(DIGITS)}`)
		.attr('dy', d => yScale(d.name) + DIMENSION.offset)
		.attr('font-size', '10px')
		.attr('text-anchor', 'end')
		.attr('alignment-baseline', 'hanging');

	container.append('g')
		.attr('transform', `translate(${DIMENSION.margin.left - DIMENSION.offset}, ${DIMENSION.margin.top - DIMENSION.offset})`)
		.selectAll('text')
		.data(uniqueRecipientArray)
		.enter()
		.append('text')
		.text(d => `${d.name} | ${d.count} | $${d.amount.toExponential(DIGITS)}`)
		.attr('dx', d => xScale(d.name) + DIMENSION.offset)
		.attr('transform', d => `rotate(-90, ${xScale(d.name) + DIMENSION.offset}, 0)`)
		.attr('font-size', '10px')
		.attr('text-anchor', 'start')
		.attr('alignment-baseline', 'hanging');

	container.append('g')
		.attr('transform', `translate(${DIMENSION.margin.left}, ${DIMENSION.margin.top})`)
		.selectAll('rect')
		.data(data)
		.enter()
		.append('rect')
		.attr('y', d => yScale(d.donor))
		.attr('x', d => xScale(d.recipient))
		.attr('fill', d => colorScale(d.amount))
		.attr('width', d => xScale.bandwidth())
		.attr('height', d => yScale.bandwidth());

	container.append('g')
		.attr('transform', `translate(${DIMENSION.margin.left}, ${DIMENSION.margin.top})`)
		.selectAll('line')
		.data(Object.keys(uniqueRecipient))
		.enter()
		.append('line')
		.attr('stroke', 'black')
		.attr('x1', d => xScale(d))
		.attr('y1', 0)
		.attr('x2', d => xScale(d))
		.attr('y2', DIMENSION.height - (DIMENSION.margin.top + DIMENSION.margin.bottom));

	container.append('g')
		.attr('transform', `translate(${DIMENSION.margin.left}, ${DIMENSION.margin.top})`)
		.selectAll('line')
		.data(Object.keys(uniqueDonor))
		.enter()
		.append('line')
		.attr('stroke', 'black')
		.attr('x1', 0)
		.attr('y1', d => yScale(d))
		.attr('x2', DIMENSION.width - (DIMENSION.margin.left + DIMENSION.margin.right))
		.attr('y2', d => yScale(d));

	const legend = container.append('g')
		.attr('transform', 'translate(15, 70)')
		.attr('width', 160)
		.attr('height', 35);

	const gradient = legend.append('defs')
		.append('linearGradient')
		.attr('id', 'gradient')
		.attr('x1', '0%')
		.attr('y1', '0%')
		.attr('x2', '100%')
		.attr('y2', '0%');

	gradient.append('stop')
		.attr('offset', '0%')
		.attr('stop-color', 'AntiqueWhite');

	gradient.append('stop')
		.attr('offset', '100%')
		.attr('stop-color', 'blue');

	legend.append('rect')
		.attr('width', 150)
		.attr('height', 25)
		.style('fill', 'url(#gradient)');

	const scale = d3.scaleLinear()
		.range([0, 150])
		.domain([min, max]);
	const axis = d3.axisBottom(scale)
		.tickFormat(v => v / 1e6);

	legend.append('g')
		.attr('transform', 'translate(0, 25)')
		.call(axis)
		.append('text')
		.text('Millions ($)')
		.attr('dx', 75)
		.attr('dy', 35)
		.attr('text-anchor', 'middle')
		.attr('fill', 'black');

});
