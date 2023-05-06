use rand::Rng;
use std::{fs, io, time::Instant};

fn merge_sort<T: std::cmp::PartialOrd + Clone>(arr: &mut [T]) {
    if arr.len() > 1 {
        let mid = arr.len() / 2;
        let (left, right) = arr.split_at_mut(mid);

        merge_sort(left);
        merge_sort(right);

        let mut i = 0;
        let mut j = 0;
        let mut k = 0;

        let mut temp = Vec::with_capacity(mid * 2);

        while i < left.len() && j < right.len() {
            if left[i] <= right[j] {
                temp.push(left[i].clone());
                i += 1;
            } else {
                temp.push(right[j].clone());
                j += 1;
            }
        }

        while i < left.len() {
            temp.push(left[i].clone());
            i += 1;
        }

        while j < right.len() {
            temp.push(right[j].clone());
            j += 1;
        }

        while k < arr.len() {
            arr[k] = temp[k].clone();
            k += 1;
        }
    }
}

fn generate_string_arr(size: usize) -> Vec<String> {
    let contents =
        fs::read_to_string("E:/HTML Academy/проекты на Python/rust-projects/rust-app/src/text.txt")
            .expect("Something went wrong reading the file");
    let new_contents = contents
        .replace(&[',', '.', '?', '!', ':', ';'][..], "")
        .split_whitespace()
        .map(|word| word.to_string())
        .take(size)
        .collect::<Vec<String>>();
    println!("Массив заполнен {} строками", new_contents.len());
    return new_contents;
}

fn new_rand_arr<T: rand::distributions::uniform::SampleUniform + Copy>(
    arr: &mut [T],
    start: T,
    end: T,
) {
    let mut rng = rand::thread_rng();
    for i in 0..arr.len() {
        arr[i] = rng.sample(rand::distributions::Uniform::new(start, end));
    }
}

fn cycle_sort<T: std::cmp::PartialOrd + Clone>(arr: &mut [T]) {
    let mut results = [0; 12];
    for i in 0..12 {
        let start = Instant::now();
        merge_sort(arr);
        let duration = start.elapsed();
        results[i] = duration.as_micros();
    }
    let sum: u128 = results.iter().sum();
    let res: u32 = ((sum - results.iter().max().unwrap() - results.iter().min().unwrap()) / 10)
        .try_into()
        .unwrap();
    println!(
        "Среднее время выполнения(без учета максимального и минимального) = {:?}",
        res
    );
    println!("Time elapsed in sorting is: {:?}\n", results);
}

fn set_size_arr() -> usize {
    let mut number = String::new();
    println!("Введите размер массива данных:");
    io::stdin()
        .read_line(&mut number)
        .expect("Failed to read line");
    let number: usize = number
        .trim()
        .parse()
        .expect("Invalid input; input must be a number");
    println!("Массив заполнен {} элементами\n", number);
    number
}

fn main() {
    let size = set_size_arr();

    println!("Type int");
    let mut int_arr = vec![0; size];
    new_rand_arr(&mut int_arr, 0, std::i32::MAX);
    cycle_sort(&mut int_arr);

    println!("Type float");
    let mut float_arr = vec![0.0; size];
    new_rand_arr(&mut float_arr, 0.0, std::f32::MAX);
    cycle_sort(&mut float_arr);

    println!("Type double");
    let mut double_arr = vec![0.0; size];
    new_rand_arr(&mut double_arr, 0.0, std::f64::MAX);
    cycle_sort(&mut double_arr);

    println!("Type string");
    let mut string_arr = generate_string_arr(size);
    cycle_sort(&mut string_arr);
            
}
